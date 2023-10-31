#include "Move.h"
#include <math.h>
#include <iostream>
#include "CLI.h"

std::vector<Board> getPossibleMoves(const Board & board){
    std::vector<Board> moves;
    int turn = board.isWhiteTurn() ? 1 : -1;
    bool oldEat = false;
    bool eatWithKing = false;
    int maxDeep = 0;
    for(int i = 0; i < 32; i++){
        unsigned row = i/4;
        unsigned col = (i%4)*2 + ((row+1)%2);
        if(board.getPiece(row, col) * turn > 0){
            bool eat = false;
            std::vector<Board> pieceMoves = getPiecePossibleMoves(board, row, col, eat);
            int deep = eatChainDeep(board, row, col);
            if(eat && !oldEat){
                oldEat = true;
                moves.clear();
                maxDeep = deep;
                moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
            } else if(!eat && !oldEat){
                moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
            } else if(eat && oldEat){
                if(deep > maxDeep || (deep == maxDeep && (!eatWithKing || board.isKing(row, col)))){
                    if(deep > maxDeep || (!eatWithKing && board.isKing(row, col))){
                        moves.clear();
                    }
                    maxDeep = deep;
                    eatWithKing = board.isKing(row, col);
                    moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
                }
            }
        }
    }
    return moves;
}

std::vector<Board> getPiecePossibleMoves(const Board &board, int row, int col){
    bool eat = false;
    return getPiecePossibleMoves(board, row, col, eat);
}

std::vector<Board> getPiecePossibleMoves(const Board &board, int row, int col, bool & eat){
    std::vector<Board> possibleMoves;
    int player = board.isWhite(row, col) ? 1 : -1;
    int type = board.isKing(row, col) ? 2 : 1;
    bool haveToEatKing = false;
    bool maxEatDeep = false;
    for(int i = -1;i < 2;i+=2){
        for(int j = -1;j < 2;j+=2){
            if(canMove(board, row, col, row + i, col + j) && !eat){
                Board newBoard(board);
                if(row + i == 0 || row + i == 7){
                    newBoard.setPiece(row + i, col + j, (Piece)(player*2));
                } else {
                    newBoard.setPiece(row + i, col + j, (Piece)(type*player));
                }
                newBoard.setPiece(row, col, EMPTY);
                newBoard.changeTurn();
                possibleMoves.push_back(newBoard);
            } else if (canEat(board, row, col, row + 2*i, col + 2*j) && (!haveToEatKing || board.isKing(row+1, col+1))){
                if(!eat){
                    eat = true;
                    possibleMoves.clear();
                }
                Board newBoard(board);
                bool isPromotion = false;
                if(row + 2*i == 0 || row + 2*i == 7){
                    isPromotion = true;
                    newBoard.setPiece(row + 2*i, col + 2*j, (Piece)(player*2));
                } else {
                    newBoard.setPiece(row + 2*i, col + 2*j, (Piece)(type*player));
                }
                newBoard.setPiece(row, col, EMPTY);
                newBoard.setPiece(row + i, col + j, EMPTY);
                int deep = eatChainDeep(newBoard, row + 2*i, col + 2*j)+1;
                if(deep > maxEatDeep || (deep == maxEatDeep && (!haveToEatKing || board.isKing(row+i, col+j)))){
                    haveToEatKing = board.isKing(row+i, col+j);
                    maxEatDeep = deep;
                    if(!isPromotion){
                        std::vector<Board> newMoves = getPiecePossibleMoves(newBoard, row + 2*i, col + 2*j, eat);
                        if(newMoves.empty()){
                            newBoard.changeTurn();
                            possibleMoves.push_back(newBoard);
                        } else {
                            for(int i = 0; i < newMoves.size(); i++){
                                newMoves[i].changeTurn();
                            }
                            possibleMoves.insert(possibleMoves.end(), newMoves.begin(), newMoves.end());
                        }
                    } else {
                        newBoard.changeTurn();
                        possibleMoves.push_back(newBoard);
                    }
                }
            }
        }
    }

    return possibleMoves;
}

bool canMove(const Board & board, int row, int col, int newRow, int newCol){
    bool toReturn = false;
    int player = board.isWhite(row, col) ? 1 : -1;
    int type = board.isKing(row, col) ? 2 : 1;
    if(board.isValid(newRow, newCol) && abs(newRow-row) == 1 && abs(newCol-col) == 1 && (type == 2 || player != newRow-row)){
        if(board.isEmpty(newRow, newCol)){
            toReturn = true;
        }
    }
    return toReturn;
}

bool canEat(const Board & board, int row, int col, int newRow, int newCol){
    bool toReturn = false;
    int player = board.isWhite(row, col) ? 1 : -1;
    int type = board.isKing(row, col) ? 2 : 1;
    if(board.isValid(newRow, newCol) && abs(newRow-row) == 2 && abs(newCol-col) == 2 && (type == 2 || player != (newRow-row)/2)){
        if (!board.isEmpty(row+((newRow-row)/2), col+((newCol-col)/2)) && board.isWhite(row+((newRow-row)/2), col+((newCol-col)/2)) != board.isWhite(row, col)){
            if(!board.isKing(row+((newRow-row)/2), col+((newCol-col)/2)) || type == 2){ 
                if(board.isEmpty(newRow, newCol)){
                    toReturn = true;
                }
            }
        }
    }
    return toReturn;
}

int eatChainDeep(const Board & board, int row, int col){
    int deep = 0;
    for(int i=-1;i<2;i+=2){
        for(int j=-1;j<2;j+=2){
            if(canEat(board, row, col, row + 2*i, col + 2*j)){
                Board newBoard(board);
                newBoard.setPiece(row + 2*i, col + 2*j, board.getPiece(row, col));
                newBoard.setPiece(row + 2*i, col + 2*j, board.getPiece(row, col));
                newBoard.setPiece(row, col, EMPTY);
                newBoard.setPiece(row + i, col + j, EMPTY);
                int subDeep = eatChainDeep(newBoard, row + 2*i, col + 2*j);
                if(deep < subDeep+1){
                    deep = subDeep+1;
                }
            }
        }
    }
    return deep;
}

bool checkMove(const Board & prevBoard, const Board & nextBoard){
    bool toReturn = false;
    std::vector<Board> possibleMoves = getPossibleMoves(prevBoard);
    for(int i = 0; i < possibleMoves.size(); i++){
        if(possibleMoves[i] == nextBoard){
            toReturn = true;
            break;
        }
    }
    return toReturn;
}

Board makeMove(const Board & prevBoard, int row, int col, int newRow, int newCol){
    Board nextBoard;
    bool eat = false;
    if(prevBoard.getPiece(row, col) == EMPTY || prevBoard.isWhite(row, col) != prevBoard.isWhiteTurn()){
        return prevBoard;
    }
    std::vector<Board> possibleMoves = getPiecePossibleMoves(prevBoard, row, col, eat);
    for(int i = 0; i < possibleMoves.size(); i++){
        if(possibleMoves[i].getPiece(newRow, newCol) != EMPTY){
            nextBoard = possibleMoves[i];
            break;
        }
    }
    if(prevBoard.isWhiteTurn() == nextBoard.isWhiteTurn()){
        nextBoard.changeTurn();
    }
    if(checkMove(prevBoard, nextBoard)){
        return nextBoard;
    } else {
        return prevBoard;
    }
}