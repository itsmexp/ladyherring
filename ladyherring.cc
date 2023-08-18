#include "Board.cc"
#include "CLI.cc"
#include "Move.cc"

int main() {
    Board board;
    std::vector<Board> moves = getPossibleMoves(board);
    while(moves.size() > 0)
    {
        std::cout << moves[0] << "-------------------------------";   
        board = moves[0];
        moves = getPossibleMoves(board);
    }
    return 0;
}