#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <iostream>
#include <vector>

int pc(int row, int col);

enum Piece{
    EMPTY = 0,
    WHITE = 1,
    BLACK = -1,
    WHITE_KING = 2,
    BLACK_KING = -2
};

class Board{
    Piece * board;
    bool whiteTurn;

    public:
        Board();
        Board(const Board &board);
        Board(std::string fen, bool whiteTurn);
        bool isWhiteTurn() const;
        // codifica lineare delle coordinate
        Piece getPiece(int n) const;
        void setPiece(int n, Piece piece);
        bool isEnemy(int n) const;
        bool isKing(int n) const;
        bool isEmpty(int n) const;
        bool isWhite(int n) const;
        bool isRowEven(int n) const;
        bool isValid(int n) const;
        bool isPacman(int n, int m) const;
        // codifica matriciale delle coordinate
        Piece getPiece(int row, int col) const;
        void setPiece(int row, int col, Piece piece);
        bool isEnemy(int row, int col) const;
        bool isKing(int row, int col) const;
        bool isEmpty(int row, int col) const;
        bool isWhite(int row, int col) const;
        bool isValid(int row, int col) const;
        void reset();
        void changeTurn();
        ~Board();
        friend std::ostream& operator<<(std::ostream& os, const Board& board);
};

#endif //BOARD_H