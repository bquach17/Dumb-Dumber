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
<<<<<<< HEAD
    double heuristic(Board *copy, Move *move);
    std::vector<Move*> possibleMoves(Board *board, Side side);
    double miniMax(Board *copy, Move *curr, int depth, int count);
    // double* Player::dominiMove(Move *opponentsMove, int msLeft) {

=======
    double heuristic(Board *copy, Move *move, Side side);
>>>>>>> adfa86554ebbe08b9fba8e95da574e01184c6296

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
