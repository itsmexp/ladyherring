#include "Search.h"
#include <iostream>

int search(const Board & board, int depth, int alpha, int beta){
    const int maxMin = std::numeric_limits<int>::min();
    const int minMax = std::numeric_limits<int>::max();
    int type = (board.isWhiteTurn()) ? 1 : 0;
    if(depth == 0){
        return evaluate(board, 1);
    }
    std::vector<Board> moves = getPossibleMoves(board);
    if(moves.size() == 0){
        return (type == 1) ? maxMin : minMax;
    }
    if(board.isWhiteTurn()){
        for(auto it = moves.begin(); it != moves.end(); it++){
            int retval = search(*it, depth - 1, alpha, beta);
            alpha = (alpha >= retval) ? alpha : retval;
            if(beta <= alpha){
                break;
            }
        }
        return alpha;
    } else {
        for(auto it = moves.begin(); it != moves.end(); it++){
            int retval = search(*it, depth - 1, alpha, beta);
            beta = (beta <= retval) ? beta : retval;
            if(beta <= alpha){
                break;
            }
        }
        return beta;
    }
}

Board bestMove(const Board & board){
    const int maxMin = std::numeric_limits<int>::min();
    const int minMax = std::numeric_limits<int>::max();
    int type = (board.isWhiteTurn()) ? 1 : 0;
    int depth = 5;
    std::vector<Board> moves = getPossibleMoves(board);
    if(moves.size() == 0){
        return board;
    }

    int bestScore = 0;
    Board bestBoard;
    for(auto it = moves.begin(); it != moves.end(); it++){
        int score = -search(*it, depth, maxMin, minMax) * type;
        if(score > bestScore || it == moves.begin()){
            bestScore = score;
            bestBoard = *it;
        }
    }
    return bestBoard;
}
