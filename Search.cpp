#include "Search.h"
#include "Board.h"
#include "Evaluate.h"
#include "Move.h"
#include <vector>

int search(const Board & board, int depth, int alpha, int beta){
    if(depth == 0){
        return evaluate(board, 1);
    }
    std::vector<Board> moves = getPossibleMoves(board);
    if(moves.size() == 0){
        return evaluate(board, 1);
    }
    int bestScore = 0;
    for(auto it = moves.begin(); it != moves.end(); it++){
        int score = -search(*it, depth - 1, alpha, beta);
        if(score > bestScore || it == moves.begin()){
            bestScore = score;
        }
        if(bestScore > alpha){
            alpha = bestScore;
        }
    }
    return bestScore;
}

Board bestMove(const Board & board){
    std::vector<Board> moves = getPossibleMoves(board);
    if(moves.size() == 0){
        return board;
    }
    int bestScore = 0;
    Board bestBoard;
    for(auto it = moves.begin(); it != moves.end(); it++){
        int score = evaluate(*it, 1);
        if(score > bestScore || it == moves.begin()){
            bestScore = score;
            bestBoard = *it;
        }
    }
    return bestBoard;
}
