#ifndef CLI_H
#define CLI_H


#include "Board.h"
#include <string>
#include <regex>
#include <vector>
#include <iostream>

void startCLI(Board & board);
char getPieceChar(Piece p);
void printBoard(const Board & board);
std::string getFEN(const Board & board);
void executeCommand(Board & board, std::string command, std::vector<std::string> & params);
void commandHelp();
void commandPrint(const Board & board);
void commandFEN(const Board & board);
void commandMove(Board & board, std::vector<std::string> & params);
void commandComputerMove(Board & board, std::vector<std::string> & params);
void commandReset(Board & board);
void commandCreateFromFEN(Board & board, std::vector<std::string> & params);
void commandClear();

#endif //CLI_H