#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    this->side = side;
    bestMove = nullptr;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    if(bestMove != nullptr) delete bestMove;
}

/*
 * Does depth first search through possible moves.
 * Calculates and returns minimax of stones score.
 */
int Player::miniMax(Side turn, Board b, int depth) {
    if(depth == 0) {
        return b.score(side);
    }
    int factor = -1;
    if(side == turn) factor = 1;
    int mmScore = factor * -1000;
    Move *bMove = nullptr;
    Side next = (turn == BLACK) ? WHITE : BLACK;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move *move = new Move(i, j);
            if (b.checkMove(move, turn)) {
                Board newb = b.copy();
                newb.doMove(move, turn);
                int nscore = miniMax(next, newb, depth - 1);
                if(factor * nscore >= factor * mmScore) {
                    mmScore = nscore;
                    bMove = move;
                }
                else delete move;
            }
            else delete move;
        }
    }
    bestMove = bMove;
    return mmScore;
}

/*
 * Makes first possible valid move.
 */
Move *Player::randMove() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move *move = new Move(i, j);
            if (board.checkMove(move, side)) {
                board.doMove(move, side);
                return move;
            }
        }
    }
    return nullptr;
}

/*
 * Makes move with greatest immediate gain.
 */
Move *Player::greedyMove() {
    // simply chooses move with highest score
    int maxScore = 0;
    Move *maxMove = nullptr;
    Board newBoard;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move *move = new Move(i, j);
            if (board.checkMove(move, side)) {
                newBoard = board.copy();
                newBoard.doMove(move, side);
                if (newBoard.count(side) >= maxScore) {
                    maxScore = newBoard.count(side);
                    if(maxMove != nullptr) delete maxMove;
                    maxMove = move;
                }
                else delete move;
            }
            else delete move;
        }
    }
    board.doMove(maxMove, side);
    return maxMove;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    // Makes opponent's move and checks for valid moves
    Side other = (side == BLACK) ? WHITE : BLACK;
    board.doMove(opponentsMove, other);
    if(!board.hasMoves(side)) return nullptr;

    if(testingMinimax) {
       miniMax(side, board, 2);
       board.doMove(bestMove, side);
       return bestMove;
    }

    return greedyMove();
}
