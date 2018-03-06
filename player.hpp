#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
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
    double heuristic(Board *copy, Move *move);
    std::vector<Move*> possibleMoves(Board *board, Side side);
    double miniMax(Board *copy, Move *curr, int depth, int count);
    // double* Player::dominiMove(Move *opponentsMove, int msLeft) {


    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
