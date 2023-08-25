#ifndef MOVE_H
#define MOVE_H

#include "Board.h"
#include <vector>
#include <iostream>

std::vector<Board> getPossibleMoves(const Board & board);
std::vector<Board> getPiecePOssibleMoves(const Board & board, int row, int col);
std::vector<Board> getPiecePossibleMoves(const Board & board, int row, int col, bool & eat);
bool canMove(const Board & board, int row, int col, int newRow, int newCol);
bool canEat(const Board & board, int row, int col, int newRow, int newCol);
int eatChainDeep(const Board & board, int row, int col);
bool checkMove(const Board & prevBoard, const Board & nextBoard);
Board makeMove(const Board & prevBoard, int row, int col, int newRow, int newCol);
#endif