#include "Move.h"

int moveOffset[4][2] = {{-4, -3}, {-5, -4}, {4, 5}, {3, 4}};
int jumpOffset[4] = {-7, -9, 9, 7};

enum Direction{
    NE = 0,
    NW = 1,
    SE = 2,
    SW = 3
};

std::vector<Board> getPossibleMoves(const Board & board)
{
    std::vector<Board> moves;
    if(board.isWhiteTurn())
    {
        for(int i = 0; i < 32; i++)
        {
            if(board.getPiece(i) > 0)
            {
                std::vector<Board> pieceMoves = getPiecePossibleMoves(board, i);
                moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }
    else
    {
        for(int i = 0; i < 32; i++)
        {
            if(board.getPiece(i) < 0)
            {
                std::vector<Board> pieceMoves = getPiecePossibleMoves(board, i);
                moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }
    return moves;
}

std::vector<Board> getPiecePossibleMoves(const Board & board , int n)
{
    if (board.isKing(n))
        return getKingPossibleMoves(board, n);
    else
        return getManPossibleMoves(board, n);
}

std::vector<Board> getKingPossibleMoves(const Board &board, int n)
{
    std::vector<Board> possibleMoves;
    int offset = board.isRowEven(n) ? 1 : 0;
    for(int i = 0; i < 4; i++){
        if(board.isValid(n + moveOffset[i][offset]) && board.isEmpty(n + moveOffset[i][offset]) && !board.isPacman(n, n + moveOffset[i][offset]))
        {
            Board newBoard(board);
            newBoard.setPiece(n + moveOffset[i][offset], newBoard.getPiece(n));
            newBoard.setPiece(n, EMPTY);
            newBoard.changeTurn();
            possibleMoves.push_back(newBoard);
        }
    }
    return possibleMoves;
}

std::vector<Board> getManPossibleMoves(const Board &board, int n)
{
    std::vector<Board> possibleMoves;
    int offset = board.isRowEven(n) ? 1 : 0;
    if(board.isWhiteTurn())
    {
        for(int i = 0; i < 2; i++)
        {
            if(board.isValid(n + moveOffset[i][offset]) && board.isEmpty(n + moveOffset[i][offset]) && !board.isPacman(n, n + moveOffset[i][offset]))
            {
                Board newBoard(board);
                newBoard.setPiece(n + moveOffset[i][offset], newBoard.getPiece(n));
                newBoard.setPiece(n, EMPTY);
                newBoard.changeTurn();
                possibleMoves.push_back(newBoard);
            }
        }
    }
    else
    {
        for(int i = 2; i < 4; i++)
        {
            if(board.isValid(n + moveOffset[i][offset]) && board.isEmpty(n + moveOffset[i][offset]) && !board.isPacman(n, n + moveOffset[i][offset]))
            {
                Board newBoard(board);
                newBoard.setPiece(n + moveOffset[i][offset], newBoard.getPiece(n));
                newBoard.setPiece(n, EMPTY);
                newBoard.changeTurn();
                possibleMoves.push_back(newBoard);
            }
        }
    }
    return possibleMoves;
}
