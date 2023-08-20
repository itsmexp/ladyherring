#include "Board.h"

Board::Board()
{
    board = new Piece[32];
    for(int i = 0; i < 32; i++){
        if(i < 12)
            board[i] = BLACK;
        else if(i > 19)
            board[i] = WHITE;
        else
            board[i] = EMPTY;
    }
    whiteTurn = true;
}

// Copy constructor
Board::Board(const Board &board)
{
    this->board = new Piece[32];
    for(int i = 0; i < 32; i++)
        this->board[i] = board.board[i];
    this->whiteTurn = board.whiteTurn;
}

Board::Board(std::string fen, bool whiteTurn = true)
{
    board = new Piece[32];
    int i = 7;
    int j = 0;
    for(char c : fen)
    {
        switch (c)
        {
            case 'w':
                board[pc(i, j)] = WHITE;
                j+=2;
                break;
            case 'b':
                board[pc(i, j)] = BLACK;
                j+=2;
                break;
            case 'W':
                board[pc(i, j)] = WHITE_KING;
                j+=2;
                break;
            case 'B':
                board[pc(i, j)] = BLACK_KING;
                j+=2;
                break;
            case '/':
                i--;
                j = 0;
                break;
            default:
                j += (c - '0') * 2;
                break;
        }
    }
    this->whiteTurn = whiteTurn;
}

bool Board::isWhiteTurn() const
{
    return whiteTurn;
}

Piece Board::getPiece(int n) const
{
    return board[n];
}

void Board::setPiece(int n, Piece piece)
{
    board[n] = piece;
}

bool Board::isEnemy(int n) const
{
    if (whiteTurn)
        return board[n] < 0;
    else
        return board[n] > 0;
}

bool Board::isKing(int n) const
{
    return board[n] == WHITE_KING || board[n] == BLACK_KING;
}

bool Board::isEmpty(int n) const
{
    return board[n] == EMPTY;
}

bool Board::isWhite(int n) const
{
    return board[n] > 0;
}

void Board::changeTurn()
{
    whiteTurn = !whiteTurn;
}

Board::~Board()
{
}

int pc(int row, int col)
{
    return row * 4 + col / 2;
}

bool Board::isRowEven(int n) const
{
    return (n / 4) % 2 == 0;
}

bool Board::isValid(int n) const
{
    return n < 32 && n >= 0;
}

Piece Board::getPiece(int row, int col) const{
    return getPiece(pc(row, col));
}
void Board::setPiece(int row, int col, Piece piece){
    setPiece(pc(row, col), piece);
}
bool Board::isEnemy(int row, int col) const{
    return isEnemy(pc(row, col));
}
bool Board::isKing(int row, int col) const{
    return isKing(pc(row, col));
}
bool Board::isEmpty(int row, int col) const{
    return isEmpty(pc(row, col));
}
bool Board::isWhite(int row, int col) const{
    return isWhite(pc(row, col));
}
bool Board::isValid(int row, int col) const{
    return (row+col)%2 == 1 && row >= 0 && row <= 7 && col >= 0 && col <= 7 && isValid(pc(row, col));
}

void Board::reset()
{
    for(int i = 0; i < 32; i++){
        if(i < 12)
            board[i] = BLACK;
        else if(i > 19)
            board[i] = WHITE;
        else
            board[i] = EMPTY;
    }
    whiteTurn = true;
}

bool Board::isPacman(int n, int m) const
{
    if(n % 4 == 0 && m % 4 == 3)
        return true;
    if(n % 4 == 3 && m % 4 == 0)
        return true;
    return false;
}
