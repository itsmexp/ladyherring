#ifndef SEARCHI_H
#define SEARCHI_H

#include "Board.h"
#include "Evaluate.h"
#include "Move.h"
#include <vector>

int search(const Board & board, int depth, int alpha, int beta);
Board bestMove(const Board & board);

#endif //SEARCH_H