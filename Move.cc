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
    //std::cout << "inizio" << std::endl;
    for(int i = 0; i < 32; i++){
        unsigned row = i/4;
        unsigned col = (i%4)*2 + ((row+1)%2);
        if(board.getPiece(row, col) * turn > 0){
            bool eat = false;
            std::vector<Board> pieceMoves = getPiecePossibleMoves(board, row, col, eat);
            int deep = eatChainDeep(board, row, col);
            if(eat && !oldEat){
                //std::cout << "qui"<< std::endl;
                oldEat = true;
                for(auto it = pieceMoves.begin();it != pieceMoves.end();it++){
                    printBoard(*it);
                }
                moves.clear();
                maxDeep = deep;
                moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
            } else if(!eat && !oldEat){
                //std::cout << "quo"<< std::endl;
                moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
            } else if(eat && oldEat){
                //std::cout << "qua"<< std::endl;
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
    //printBoard(board);
    //std::cout << "moves.size() " << moves.size()<< std::endl;
    return moves;
}

std::vector<Board> getPiecePOssibleMoves(const Board &board, int row, int col){
    bool eat = false;
    return getPiecePossibleMoves(board, row, col, eat);
}

std::vector<Board> getPiecePossibleMoves(const Board &board, int row, int col, bool & eat){
    std::vector<Board> possibleMoves;
    //std::cout << "row: " << row << " col: " << col << std::endl;
    int player = board.isWhite(row, col) ? 1 : -1;
    int type = board.isKing(row, col) ? 2 : 1;
    bool haveToEatKing = false;
    bool maxEatDeep = false;
    for(int i = -1;i < 2;i+=2){
        for(int j = -1;j < 2;j+=2){
            //std::cout << "i: " << i << " j: " << j << " canMove: "<< canMove(board, row, col, row + i, col + j) << " canEat: " << canEat(board, row, col, row + 2*i, col + 2*j) << std::endl;
            if(canMove(board, row, col, row + i, col + j) && !eat){
                //std::cout << "row: " << row << " col: " << col << " newRow: " << row + i << " newCol: " << col + j << std::endl;
                Board newBoard(board);
                if(row + i == 0 || row + i == 7){
                    newBoard.setPiece(row + i, col + j, (Piece)(player*2));
                } else {
                    newBoard.setPiece(row + i, col + j, (Piece)(type*player));
                }
                newBoard.setPiece(row, col, EMPTY);
                if(i == -1 && j == 1)
                newBoard.changeTurn();
                possibleMoves.push_back(newBoard);
            } else if (canEat(board, row, col, row + 2*i, col + 2*j) && (!haveToEatKing || board.isKing(row+1, col+1))){
                if(!eat){
                    eat = true;
                    possibleMoves.clear();
                }
                Board newBoard(board);
                if(row + 2*i == 0 || row + 2*i == 7){
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
                    std::vector<Board> newMoves = getPiecePossibleMoves(newBoard, row + 2*i, col + 2*j, eat);
                    if(newMoves.empty()){
                        newBoard.changeTurn();
                        possibleMoves.push_back(newBoard);
                    } else {
                        possibleMoves.insert(possibleMoves.end(), newMoves.begin(), newMoves.end());
                    }
                }
            }
            //std::cout << "fine ciclo: " << possibleMoves.size() << std::endl;
        }
    }

    return possibleMoves;
}

bool canMove(const Board & board, int row, int col, int newRow, int newCol){
    bool toReturn = false;
    int player = board.isWhite(row, col) ? 1 : -1;
    int type = board.isKing(row, col) ? 2 : 1;
    //std::cout<<std::endl<<"row: " << row << " col: " << col << " newRow: " << newRow << " newCol: " << newCol << std::endl;
    //std::cout << " isValid " << board.isValid(newRow, newCol) << " abs(newRow-row) " << abs(newRow-row) << " abs(newCol-col) " << abs(newCol-col) << " type " << type << " player " << player << " newRow-row " << newRow-row << std::endl;
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
    //std::cout << "possibleMoves.size(): " << possibleMoves.size() << std::endl;
    for(int i = 0; i < possibleMoves.size(); i++){
        //std::cout << "possibleMoves[" << i << "]: " << std::endl;
        //printBoard(possibleMoves[i]);
        if(possibleMoves[i] == nextBoard){
            toReturn = true;
            break;
        }
    }
    return toReturn;
}

Board makeMove(const Board & prevBoard, int row, int col, int newRow, int newCol){
    //std::cout << "row: " << row << "col: " << col << "newRow: " << newRow << "newCol: " << newCol << std::endl;
    //std::cout << "prevBoard.getPiece(row, col): " << prevBoard.getPiece(row, col) << std::endl;
    Board nextBoard;
    bool eat = false;
    if(prevBoard.getPiece(row, col) == EMPTY || prevBoard.isWhite(row, col) != prevBoard.isWhiteTurn()){
        std::cout << "mossa non valida" << std::endl;
        //std::cout << "prevBoard.getPiece(row, col): " << prevBoard.getPiece(row, col) << " prevBoard.isWhite(row, col): " << prevBoard.isWhite(row, col) << " prevBoard.isWhiteTurn(): " << prevBoard.isWhiteTurn() << std::endl;
        return prevBoard;
    }
    std::vector<Board> possibleMoves = getPiecePossibleMoves(prevBoard, row, col, eat);
    for(int i = 0; i < possibleMoves.size(); i++){
        //std::cout << "possibleMoves[" << i << "].getPiece(newRow, newCol): " << possibleMoves[i].getPiece(newRow, newCol) << std::endl;
        if(possibleMoves[i].getPiece(newRow, newCol) != EMPTY){
            //std::cout << "sono qui "<< std::endl;
            nextBoard = possibleMoves[i];
            //printBoard(nextBoard);
            break;
        }
    }
    if(prevBoard.isWhiteTurn() == nextBoard.isWhiteTurn()){
        nextBoard.changeTurn();
    }
    if(checkMove(prevBoard, nextBoard)){
        std::cout << "mossa valida" << std::endl;
        return nextBoard;
    } else {
        std::cout << "mossa non valida1" << std::endl;
        return prevBoard;
    }
}