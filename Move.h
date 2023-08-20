#ifndef MOVE_H
#define MOVE_H

#include "Board.h"
#include <vector>
#include <iostream>

std::vector<Board> getPossibleMoves(const Board & board);
std::vector<Board> getPiecePossibleMoves(const Board & board, int row, int col, bool & eat);

#endif