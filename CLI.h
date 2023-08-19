#ifndef CLI_H
#define CLI_H

#include "Board.h"
#include <string>

char getPieceChar(Piece p);
void printBoard(const Board & board);
std::string FEN(const Board & board);

#endif //CLI_H