#ifndef EVALUATE_H
#define EVALUATE_H

#include "Board.h"

int evaluate(const Board & board, int type);
int getPieceValue(Piece p);
int simpleEval(const Board & board);
int complexEval(const Board & board); 

#endif //EVALUATE_H