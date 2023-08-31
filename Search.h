#ifdef SEARCH_H
#define SEARCH_H

#include "Board.h"
#include "Evaluate.h"
#include <vector>

int search(const Board & board, int depth, int alpha, int beta){
    if(dept = 0){
        return evaluate(board);
    }
    std::vector<Board> moves = getPossibleMoves(board);
    if(moves.size() == 0){
        return evaluate(board);
    }
    int bestScore = 0;
    for(auto it = moves.begin(); it != moves.end(); it++){
        int score = -search(*it, depth - 1);
        if(score > bestScore || it = moves.begin()){
            bestScore = score;
        }
        if(bestScore > alpha){
            alpha = bestScore;
        }
    }
    return bestScore;
}

Board bestMove(const Board & board, int depth){
    std::vector<Board> moves = getPossibleMoves(board);
    if(moves.size() == 0){
        return board;
    }
    int bestScore = 0;
    Board bestBoard;
    for(auto it = moves.begin(); it != moves.end(); it++){
        int score = -search(*it, depth - 1);
        if(score > bestScore || it = moves.begin()){
            bestScore = score;
            bestBoard = *it;
        }
    }
    return bestBoard;
}

#endif //SEARCH_H