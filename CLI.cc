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

void printBoard(const Board & b)
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
    std::cout << "FEN: " << FEN(b) << std::endl;
}

std::string FEN(const Board &board)
{
    std::string fen = "";
    std::string tempFen = "";
    int spaceCount = 0;
    for(int i = 0; i < 32; i++)
    {
        if (board.getPiece(i) == EMPTY)
            spaceCount++;
        else
        {
            if (spaceCount > 0)
            {
                tempFen += std::to_string(spaceCount);
                spaceCount = 0;
            }
            tempFen += getPieceChar(board.getPiece(i));
        }
        if(i % 4 == 3){
            if (spaceCount > 0)
            {
                tempFen += std::to_string(spaceCount);
                spaceCount = 0;
            }
            fen = tempFen + "/" + fen;
            tempFen = "";
        }
    }
    fen = fen.substr(0, fen.length() - 1);
    fen += " ";
    fen += board.isWhiteTurn() ? "w" : "b";
    return fen;
}

std::ostream & operator<<(std::ostream & os, const Board & board)
{
    os << FEN(board);
    return os;
}