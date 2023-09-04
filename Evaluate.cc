#include "Evaluate.h"

int evaluate(const Board &board, int type = 0)
{
    switch(type)
    {
        default:
            return simpleEval(board);
        case 1:
            return complexEval(board);
    }
}

int getPieceValue(Piece p)
{
    switch(int(p)){
        case 0:
            return 0;
        case 1:
            return 100;
        case -1:
            return -100;
        case 2:
            return 300;
        case -2:
            return -300;
        default:
            return 0;
    };
}

int simpleEval(const Board &board)
{
    int value = 0;
    for (int i = 0; i < 32; i++)
    {
        value += getPieceValue(board.getPiece(i));
    }
    return value;
}

int complexEval(const Board &board)
{
    return simpleEval(board);
}
