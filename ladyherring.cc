#include "Board.cc"
#include "CLI.cc"
#include "Move.cc"

int main() {
    Board board;
    std::vector<Board> moves = getPossibleMoves(board);
    printBoard(moves[0]);   
    return 0;
}