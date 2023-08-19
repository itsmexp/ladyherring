#include "Board.cc"
#include "CLI.cc"
#include "Move.cc"

int main() {
    Board board;
    std::vector<Board> moves = getPossibleMoves(board);
    while (moves.size() > 0) {
        std::cout << moves[0] << std::endl;
        moves = getPossibleMoves(moves[0]);
    } 
    return 0;
}