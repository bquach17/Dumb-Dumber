#include "player.hpp"
#include <vector>
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
    // Fill in weights into our map
    weights[make_tuple(0, 0)] = 4; 
    weights[make_tuple(0, 1)] = -3; 
    weights[make_tuple(0, 2)] = 2; 
    weights[make_tuple(0, 3)] = 2; 
    weights[make_tuple(0, 4)] = 2; 
    weights[make_tuple(0, 5)] = 2; 
    weights[make_tuple(0, 6)] = -3;
    weights[make_tuple(0, 7)] = 4;
    weights[make_tuple(1, 0)] = -3;
    weights[make_tuple(1, 1)] = -4;
    weights[make_tuple(1, 2)] = -1;
    weights[make_tuple(1, 3)] = -1;
    weights[make_tuple(1, 4)] = -1;
    weights[make_tuple(1, 5)] = -1;
    weights[make_tuple(1, 6)] = -4;
    weights[make_tuple(1, 7)] = -3;
    weights[make_tuple(2, 0)] = 2;
    weights[make_tuple(2, 1)] = -1;
    weights[make_tuple(2, 2)] = 1;
    weights[make_tuple(2, 3)] = 0;
    weights[make_tuple(2, 4)] = 0;
    weights[make_tuple(2, 5)] = 1;
    weights[make_tuple(2, 6)] = -1;
    weights[make_tuple(2, 7)] = 2;
    weights[make_tuple(3, 0)] = 2;
    weights[make_tuple(3, 1)] = -1;
    weights[make_tuple(3, 2)] = 0;
    weights[make_tuple(3, 3)] = 1;
    weights[make_tuple(3, 4)] = 1;
    weights[make_tuple(3, 5)] = 0;
    weights[make_tuple(3, 6)] = -1;
    weights[make_tuple(3, 7)] = 2;
    weights[make_tuple(4, 0)] = 2;
    weights[make_tuple(4, 1)] = -1;
    weights[make_tuple(4, 2)] = 1;
    weights[make_tuple(4, 3)] = 1;
    weights[make_tuple(4, 4)] = 1;
    weights[make_tuple(4, 5)] = 1;
    weights[make_tuple(4, 6)] = -1;
    weights[make_tuple(4, 7)] = 2;
    weights[make_tuple(5, 0)] = 2;
    weights[make_tuple(5, 1)] = -1;
    weights[make_tuple(5, 2)] = 1;
    weights[make_tuple(5, 3)] = 0;
    weights[make_tuple(5, 4)] = 0;
    weights[make_tuple(5, 5)] = 1;
    weights[make_tuple(5, 6)] = -1;
    weights[make_tuple(5, 7)] = 2;
    weights[make_tuple(6, 0)] = -3;
    weights[make_tuple(6, 1)] = -4;
    weights[make_tuple(6, 2)] = -1;
    weights[make_tuple(6, 3)] = -1;
    weights[make_tuple(6, 4)] = -1;
    weights[make_tuple(6, 5)] = -1;
    weights[make_tuple(6, 6)] = -4;
    weights[make_tuple(6, 7)] = -3;
    weights[make_tuple(7, 0)] = 4; 
    weights[make_tuple(7, 1)] = -3; 
    weights[make_tuple(7, 2)] = 2; 
    weights[make_tuple(7, 3)] = 2; 
    weights[make_tuple(7, 4)] = 2; 
    weights[make_tuple(7, 5)] = 2; 
    weights[make_tuple(7, 6)] = -3;
    weights[make_tuple(7, 7)] = 4;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete board;
}

Move *Player::doMove(Move *opponentsMove, int msLeft)
{
    // Do Minimax algorithm
    return doMove2(opponentsMove, msLeft);
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
Move *Player::doMove1(Move *opponentsMove, int msLeft) {

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
                    if (heuristic(copy, move, color) > max_score)
                    {
                        max_score = heuristic(copy, move, color);
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

std::vector<Move*> Player::possibleMoves(Board *check, Side side)
{
    vector<Move*> possible= {};
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Move *move = new Move(0, 0);
            move->setX(i);
            move->setY(j);

            if (check->checkMove(move, side))
            {
                possible.push_back(move);  
            }
        }
    }
    return possible;
}

Move* Player::doMove2(Move *opponentsMove, int msLeft) {

    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    board->doMove(opponentsMove, opponent);
    Move *move = new Move(0, 0);
    double max_score = -100000;
    if (!board->hasMoves(color) || board->isDone())
    {
        return nullptr;
    }
    else
    {
        std::vector<Move*> lst = possibleMoves(board, color);
        for (unsigned int i = 0; i < lst.size(); i++)
        {
            Board *copy = board -> copy();
            double save = miniMax(copy, lst[i], 4, 1);

            if (save > max_score)
            {
                max_score = save;
                move = lst[i];
            }
            delete copy;

        }
        if (board->hasMoves(color))
        {
            board->doMove(move, color);
            return move;
        }
    }
    return nullptr;
}

//minimum score of possible moves within intended depth
//count: current depth 
//always start from second level (count always set as 1 is doMove)
double Player::miniMax(Board *copy, Move *curr, int depth, int count)
{
    count++;
    double min = 9999999.9;
    Side playing = color;
    Side notplaying = color;

    if (count % 2 != 0) //my turn
    {
        notplaying = opponent;
    }
    else //opponents turn
    {
        playing = opponent;
    }
    copy -> doMove(curr, notplaying);


    if (count > depth) //Base: reached intended level
    {
        return heuristic(copy, curr, playing);
    }
    else
    {
        vector<Move*> lst = possibleMoves(copy, playing);

        if (lst.size() == 0) //if no possible moves, return previous point
        {
            return heuristic(copy, curr, playing);
        }
        for (unsigned int i = 0; i < lst.size(); i++)
        {
            //debug
            // std::cerr << min << std::endl;
            // std::cerr << lst[i] -> getX() << " | " << lst[i] -> getY() << std::endl;

            Board *newCopy = copy -> copy();
            double temp = miniMax(newCopy, lst[i], depth, count);
            if (min > temp)
            {
                min = temp;
            }

            delete newCopy;
        }
        return min;
        
    }
    return -1;
} 

double Player::heuristic(Board *copy, Move *move, Side playing) {
    double value = copy->count(color) - copy->count(opponent);
    // if (playing == opponent) {
    //     return value;
    // }
    double weight = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board->get(playing, i, j))
            {
                if (playing == color)
                {
                    weight += weights[make_tuple(i, j)];
                }
                else
                    weight -= weights[make_tuple(i, j)];
            }
            else if(board->occupied(i, j)) {
                if (playing == color)
                {
                    weight -= weights[make_tuple(i, j)];
                }
                else
                {
                    weight += weights[make_tuple(i, j)];
                }
            }
        }
    }
    weight *= abs(value);
    return weight;


    // Old Heuristic
    // // Corners
    // if ((x == 0 && y == 0) || (x == 7 && y == 7) || (x == 0 && y == 7) || (x == 7 && y == 0))
    // {
    //     return value + 5*weight;
    // }
    // // Left Edge
    // else if (x == 0)
    // {
    //     if (y == 1 || y == 6)
    //     {
    //         return value + weight;
    //     }
    //     else if (y == 2 || y == 5)
    //     {
    //         return value + 11 * weight;
    //     }
    //     else
    //     {
    //         return value;
    //     }
    // }
    // // Right Edge
    // else if (x == 7)
    // {
    //     if (y == 1 || y == 6)
    //     {
    //         return value + weight;
    //     }
    //     else if (y == 2 || y == 5)
    //     {
    //         return value + 11 * weight;
    //     }
    //     else
    //     {
    //         return value;
    //     }
    // }
    // // Top Edge
    // else if (y == 0)
    // {
    //     if (x == 1 || x == 6)
    //     {
    //         return value + weight;
    //     }
    //     else if (x == 2 || x == 5)
    //     {
    //         return value + 11 * weight;
    //     }
    //     else
    //     {
    //         return value;
    //     }
    // }
    // // Bottom Edge
    // else if (y == 7)
    // {
    //     if (x == 1 || x == 6)
    //     {
    //         return value + weight;
    //     }
    //     else if (x == 2 || x == 5)
    //     {
    //         return value + 11 * weight;
    //     }
    //     else
    //     {
    //         return value;
    //     }
    // }
    // // Squares located Diagonally from squares
    // else if ((x == 1 && y == 1) || (x == 6 && y == 1) || (x == 1 && y == 6) || (x == 6 && y == 6))
    // {
    //     return value - weight;
    // }
    // return value;

}
