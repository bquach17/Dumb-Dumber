#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include <iostream>
#include "common.hpp"
#include "board.hpp"
#include <cmath>
#include <tuple>
#include <map>
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    Board *board;
    Side color;
    Side opponent;
    map<tuple<int, int>, float> weights;
    Move *doMove2(Move *opponentsMove, int msLeft);
    Move *doMove1(Move *opponentsMove, int msLeft);
    Move *doMove(Move *opponentsMove, int msLeft);
    double heuristic(Board *copy, Move *move, Side Playing);
    std::vector<Move*> possibleMoves(Board *board, Side side);
    double miniMax(Board *copy, Move *curr, int depth, int count);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
