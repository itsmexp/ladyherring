#include "Board.h"

Board::Board()
{
    board = new int[64]{ -1, 0 , -1, 0 , -1, 0 , -1, 0 ,
                         0 , -1, 0 , -1, 0 , -1, 0 , -1,
                         -1, 0 , -1, 0 , -1, 0 , -1, 0 ,
                         0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
                         0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
                         0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 ,
                         1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 ,
                         0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 };                
    whiteTurn = true;
}

// Copy constructor
Board::Board(const Board &board)
{
    this->board = new int[64];
    for(int i = 0; i < 64; i++)
        this->board[i] = board.board[i];
    this->whiteTurn = board.whiteTurn;
}

bool const Board::isWhiteTurn()
{
    return whiteTurn;
}

int const Board::getPiece(int n)
{
    return board[n];
}

void Board::setPiece(int n, int piece)
{
    board[n] = piece;
}

void Board::changeTurn()
{
    whiteTurn = !whiteTurn;
}

Board::~Board()
{
    delete[] board;
}

int pc(int row, int col)
{
    return row * 8 + col;
}
