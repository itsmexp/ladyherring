#include "Move.h"

std::vector<Board> getPossibleMoves(const Board & board){
    std::vector<Board> moves;
    int turn = board.isWhiteTurn() ? 1 : -1;
    bool eat = false;
    bool oldEat = false;
    for(int i = 0; i < 32; i++){
        unsigned row = i/4;
        unsigned col = (i%4)*2 + ((row+1)%2);
        if(board.getPiece(row, col) * turn > 0){
            std::vector<Board> pieceMoves = getPiecePossibleMoves(board, row, col, eat);
            if(eat != oldEat){
                moves.clear();
                oldEat = eat;
            }
            moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
        }
    }
    return moves;
}

std::vector<Board> getPiecePossibleMoves(const Board &board, int row, int col, bool & eat){
    std::vector<Board> possibleMoves;
    int player = board.isWhite(row, col) ? 1 : -1;
    int type = board.isKing(row, col) ? 2 : 1;
    for(int i = -1;i < 2;i+=2){
        for(int j = -1;j < 2;j+=2){
            if(board.isValid(row + i, col + j) && (type == 2 || player != i)){
                if(board.isEmpty(row + i, col + j) && !eat){
                    Board newBoard(board);
                    if(row + i == 0 || row + i == 7){
                        newBoard.setPiece(row + i, col + j, (Piece)(player*2));
                    } else {
                        newBoard.setPiece(row + i, col + j, (Piece)(type*player));
                    }
                    newBoard.setPiece(row, col, EMPTY);
                    newBoard.changeTurn();
                    possibleMoves.push_back(newBoard);
                } else if (!board.isEmpty(row+i, col+j) && board.isWhite(row+i, col+j) != board.isWhiteTurn()){
                    if(board.isValid(row + 2*i, col + 2*j) && (!board.isKing(row+i, col+i) || type == 2)){ 
                        if(board.isEmpty(row + 2*i, col + 2*j)){
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
                            std::vector<Board> newMoves = getPiecePossibleMoves(newBoard, row + 2*i, col + 2*j, eat);
                            if(newMoves.empty()){
                                newBoard.changeTurn();
                                possibleMoves.push_back(newBoard);
                            } else {
                                possibleMoves.insert(possibleMoves.end(), newMoves.begin(), newMoves.end());
                            }
                        }
                    }
                }
            }
        }
    }
    return possibleMoves;
}