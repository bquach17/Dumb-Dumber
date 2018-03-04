#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */

    board = new Board();
    color = side;
    if (color == BLACK)
    {
        opponent = WHITE;
    }
    else
    {
        opponent = BLACK;
    }

}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete board;
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

    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    board->doMove(opponentsMove, opponent);
    Move *move = new Move(0, 0);
    Move current_move(0, 0);
    double max_score = -100000;
    Board *copy = nullptr;
    if (!board->hasMoves(color) || board->isDone())
    {
        return nullptr;
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            move->setX(i);
            for (int j = 0; j < 8; j++)
            {
                move->setY(j);
                if (board->checkMove(move, color))
                {
                    copy = board->copy();
                    copy->doMove(move, color);
                    if (heuristic(copy, move) > max_score)
                    {
                        max_score = heuristic(copy, move);
                        current_move.setX(move->getX());
                        current_move.setY(move->getY());
                    }
                    delete copy;
                }
            }
        }
        move->setX(current_move.getX());
        move->setY(current_move.getY());
        if (board->hasMoves(color))
        {
            board->doMove(move, color);
            return move;
        }
    }
    return nullptr;
}

Move Player::miniMax(Board *copy, Move *ours)
{
    if (!copy -> hasMoves(color) || )
    {
        return ;
    }
    else
    {
        int min = -999;
        for (int depth = 0; depth < 2; depth++) //depth of minimax
        {
            for (int i = 0; i < 8; i++)
            {
                move->setX(i);
                for (int j = 0; j < 8; j++)
                {
                    move->setY(j);
                    if (board->checkMove(move, color))
                    {
                        copy = board->copy();
                        copy->doMove(move, color);
                        if (heuristic(copy, move) > max_score)
                        {
                            max_score = heuristic(copy, move);
                            current_move.setX(move->getX());
                            current_move.setY(move->getY());
                        }
                        delete copy;
                    }
                }
            }
            move->setX(current_move.getX());
            move->setY(current_move.getY());
            if (board->hasMoves(color))
            {
                board->doMove(move, color);
                return move;
            }
        }
    }
} 

double Player::heuristic(Board *copy, Move *move) {
    double value = copy->count(color) - copy->count(opponent);
    int x = move->getX();
    int y = move->getY();
    if ((x == 0 && y == 0) || (x == 7 && y == 7) || (x == 0 && y == 7) || (x == 7 && y == 0))
    {
        return value + 100;
    }
    return value;

}
