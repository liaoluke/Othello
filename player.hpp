#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *randMove();
    Move *greedyMove();
    int miniMaxP(Side turn, Board b, int depth, int max, int min);
    int miniMax(Side turn, Board b, int depth);
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    Board board;
    Side side;
    Move *bestMove;
    FILE *file;
};

#endif
