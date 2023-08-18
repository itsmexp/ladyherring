#ifndef MOVE_H
#define MOVE_H

#include "Board.h"
#include <vector>
#include <iostream>

std::vector<Board> getPossibleMoves(const Board & board);
std::vector<Board> getPiecePossibleMoves(const Board & board, int n);
std::vector<Board> getKingPossibleMoves(const Board & board, int n);
std::vector<Board> getManPossibleMoves(const Board & board, int n);

#endif