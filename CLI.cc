#include "CLI.h"
#include <iostream>

char getPieceChar(Piece p)
{
    switch(p)
    {
        case EMPTY:
            return ' ';
        case WHITE:
            return 'w';
        case BLACK:
            return 'b';
        case WHITE_KING:
            return 'W';
        case BLACK_KING:
            return 'B';
        default:
            return ' ';
    }
}

void printBoard(Board b)
{
    std::cout << "+---+---+---+---+---+---+---+---+" << std::endl;
    for(int i = 0; i < 64; i++){
        if(i % 2 == 1){
            std::cout << "| " << getPieceChar(b.getPiece(i/2)) << " ";
        }
        else{
            std::cout << "|   ";
        }
        if(i % 8 == 7){
            if (i % 16 != 15){
                std::cout << "| " << 8 - i/8 << std::endl;
                i++;
            }
            else 
                std::cout << "|   | " << 8 - i/8 << std::endl;
            std::cout << "+---+---+---+---+---+---+---+---+" << std::endl;
        }
        
    }
    std::cout << "  a   b   c   d   e   f   g   h" << std::endl;
}

std::ostream & operator<<(std::ostream & os, const Board & board)
{
    for(int i = 0; i < 32; i++)
    {
        if (i % 4 == 0)
            os << std::endl;
        if ((i / 4) % 2 == 0)
            os << " " << getPieceChar(board.board[i]);
        else
            os << getPieceChar(board.board[i]) << " ";
    }
    os << std::endl;
    return os;
}