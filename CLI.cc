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
    for(int i = 0; i < 32; i++)
    {
        if (i % 4 == 0)
            std::cout << std::endl << 8 - i / 4 << " ";
        if ((i / 4) % 2 == 0)
            std::cout << " " << getPieceChar(b.getPiece(i));
        else
            std::cout << getPieceChar(b.getPiece(i)) << " ";
    }
    std::cout << std::endl << "  abcdefgh" << std::endl;
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