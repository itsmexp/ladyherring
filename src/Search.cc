#include "Search.h"
#include <iostream>

// alpha-beta pruning:
int search(const Board & board, int depth, int alpha, int beta){
    // minimo intero rappresentabile
    const int maxMin = std::numeric_limits<int>::min();
    // massimo intero rappresentabile
    const int minMax = std::numeric_limits<int>::max();
    // 1 se è il turno del bianco, 0 altrimenti (per la valutazione)
    int type = (board.isWhiteTurn()) ? 1 : 0;
    // se siamo arrivati alla profondità massima, valutiamo la scacchiera
    if(depth == 0){
        return evaluate(board, 1);
    }
    // se non ci sono mosse possibili, il giocatore ha perso
    std::vector<Board> moves = getPossibleMoves(board);
    if(moves.size() == 0){
        return (type == 1) ? maxMin : minMax;
    }
    // se è il turno del bianco, massimizziamo
    if(board.isWhiteTurn()){
        // per ogni mossa possibile, calcoliamo il punteggio e aggiorniamo alpha
        for(auto it = moves.begin(); it != moves.end(); it++){
            int retval = search(*it, depth - 1, alpha, beta);
            alpha = (alpha >= retval) ? alpha : retval;
            // se alpha è maggiore di beta, possiamo interrompere la ricerca
            if(beta <= alpha){
                break;
            }
        }
        //  restituiamo alpha
        return alpha;
    // se è il turno del nero, minimizziamo
    } else {
        // per ogni mossa possibile, calcoliamo il punteggio e aggiorniamo beta
        for(auto it = moves.begin(); it != moves.end(); it++){
            int retval = search(*it, depth - 1, alpha, beta);
            beta = (beta <= retval) ? beta : retval;
            // se alpha è maggiore di beta, possiamo interrompere la ricerca
            if(beta <= alpha){
                break;
            }
        }
        // restituiamo beta
        return beta;
    }
}

// ritorna la mossa migliore per il giocatore corrente
Board bestMove(const Board & board){
    // minimo intero rappresentabile
    const int maxMin = std::numeric_limits<int>::min();
    // massimo intero rappresentabile
    const int minMax = std::numeric_limits<int>::max();
    // 1 se è il turno del bianco, 0 altrimenti (per la valutazione)
    int type = (board.isWhiteTurn()) ? 1 : 0;
    // profondità della ricerca
    int depth = 10;
    std::vector<Board> moves = getPossibleMoves(board);
    // se non ci sono mosse possibili, il giocatore ha perso
    if(moves.size() == 0){
        return board;
    }
    int bestScore = 0;
    Board bestBoard;
    for(auto it = moves.begin(); it != moves.end(); it++){
        // calcoliamo il punteggio della mossa e lo aggiorniamo se è migliore
        int score = search(*it, depth, maxMin, minMax) * type;
        if(score > bestScore || it == moves.begin()){
            bestScore = score;
            bestBoard = *it;
        }
    }
    // restituiamo la mossa migliore
    return bestBoard;
}
