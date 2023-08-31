#ifdef SEARCH_H
#define SEARCH_H

#include "Board.h"

int search(const Board & board, int depth, int alpha, int beta);
Board bestMove(const Board & board, int depth);

#endif //SEARCH_H