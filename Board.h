#ifndef BOARD_H
#define BOARD_H

#include <string>

int pc(int row, int col);

enum Piece{
    EMPTY = 0,
    WHITE = 1,
    BLACK = -1,
    WHITE_KING = 2,
    BLACK_KING = -2
};

class Board{
    int * board;
    bool whiteTurn;

    public:
        Board();
        Board(const Board &board);
        bool const isWhiteTurn();
        int const getPiece(int n);
        void setPiece(int n, int piece);
        void changeTurn();
        ~Board();
};

#endif //BOARD_H