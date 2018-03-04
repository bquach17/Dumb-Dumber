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
    Board *board;
    Side color;
    Side opponent;
    Move *doMove(Move *opponentsMove, int msLeft);
    double heuristic(Board *copy);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
