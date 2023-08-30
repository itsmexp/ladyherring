#include "CLI.h"
#include "Move.h"

void startCLI(Board &board)
{
    std::cout << "Welcome to Lady Herring!" << std::endl;
    std::cout << "Type 'help' for a list of commands." << std::endl;
    std::regex pattern("\\S+");
    std::string command;
    std::vector<std::string> params;
    do{
        params.clear();
        std::cout << "> ";
        std::getline(std::cin, command);
        for (auto it = std::sregex_iterator(command.begin(), command.end(), pattern); it != std::sregex_iterator(); ++it) {
            params.push_back(it->str());
        }
        if (params.size() == 0)
            continue;
        if (params[0] == "exit")
            break;
        command = params[0];
        params.erase(params.begin());
        eseguiComandoCLI(board, command, params);
    } while (true);
    return;
}

char getPieceChar(Piece p)
{
    switch(p)
    {
        case EMPTY:
            return ' ';
        case WHITE:
            return 'w';
        case BLACK:
            return 'b';
        case WHITE_KING:
            return 'W';
        case BLACK_KING:
            return 'B';
        default:
            return ' ';
    }
}

void printBoard(const Board & b)
{
    std::cout << "+---+---+---+---+---+---+---+---+" << std::endl;
    for(int i = 0; i < 64; i++){
        if(i % 2 == 1){
            std::cout << "| " << getPieceChar(b.getPiece(i/2)) << " ";
        }
        else{
            std::cout << "|   ";
        }
        if(i % 8 == 7){
            if (i % 16 != 15){
                std::cout << "| " << 8 - i/8 << std::endl;
                i++;
            }
            else 
                std::cout << "|   | " << 8 - i/8 << std::endl;
            std::cout << "+---+---+---+---+---+---+---+---+" << std::endl;
        }
        
    }
    std::cout << "  a   b   c   d   e   f   g   h" << std::endl;
}

std::string getFEN(const Board &board)
{
    std::string fen = "";
    std::string tempFen = "";
    int spaceCount = 0;
    for(int i = 0; i < 32; i++)
    {
        if (board.getPiece(i) == EMPTY)
            spaceCount++;
        else
        {
            if (spaceCount > 0)
            {
                tempFen += std::to_string(spaceCount);
                spaceCount = 0;
            }
            tempFen += getPieceChar(board.getPiece(i));
        }
        if(i % 4 == 3){
            if (spaceCount > 0)
            {
                tempFen += std::to_string(spaceCount);
                spaceCount = 0;
            }
            fen = tempFen + "/" + fen;
            tempFen = "";
        }
    }
    fen = fen.substr(0, fen.length() - 1);
    fen += " ";
    fen += board.isWhiteTurn() ? "w" : "b";
    return fen;
}

void eseguiComandoCLI(Board &board, std::string command, std::vector<std::string> & params)
{
    if (command == "help")
        commandHelp();
    else if (command == "move")
        commandMove(board, params);
    else if (command == "print")
        commandPrint(board);
    else if (command == "fen")
        commandFEN(board);
    else if (command == "clear")
        commandClear();
    else if (command == "reset")
        commandReset(board);
    else if (command == "create")
        commandCreateFromFEN(board, params);
    else
        std::cout << "Unknown command. Type 'help' for a list of commands." << std::endl;
}

void commandHelp()
{
    std::cout << "List of commands:" << std::endl;
    std::cout << "help: print this list" << std::endl;
    std::cout << "move <from> <to>: move a piece from <from> to <to>" << std::endl;
    std::cout << "print: print the board" << std::endl;
    std::cout << "fen: print the FEN of the board" << std::endl;
    std::cout << "create <fen>: create a board from the given FEN" << std::endl;
    std::cout << "reset: reset the board" << std::endl;
    std::cout << "clear: clear the screen" << std::endl;
    std::cout << "exit: exit the program" << std::endl;
}

void commandPrint(const Board &board)
{
    printBoard(board);
}

void commandFEN(const Board &board)
{
    std::cout << getFEN(board) << std::endl;
}

void commandMove(Board &board, std::vector<std::string> &params)
{
    if (params.size() != 2)
    {
        std::cout << "Wrong number of parameters." << std::endl;
        return;
    }
    int from = (params[0][0] - 'a' + (8 - (params[0][0] - 'a')) * 8) / 2;
    int to = (params[1][0] - 'a' + (8 - (params[1][1] - '0')) * 8 ) / 2;
    Board newBoard = makeMove(board, 8-((params[0][1] - '0')), params[0][0] - 'a', 8-((params[1][1] - '0')), params[1][0] - 'a');
    if(board == newBoard){
        std::cout << "mossa non valida" << std::endl;
    } else {
        board = newBoard;
        std::cout << "Moving from " << params[0] << " to " << params[1] << std::endl;
    }
}

void commandReset(Board &board)
{
    board.reset();
}

void commandCreateFromFEN(Board &board, std::vector<std::string> &params)
{
    if (params.size() > 2 || params.size() < 1)
    {
        std::cout << "Wrong number of parameters." << std::endl;
        return;
    }
    if (params.size() == 1)
    {
        board = Board(params[0]);
        return;
    } else{
        bool turn = params[1] == "w";
        board = Board(params[0], turn);
    }
}

void commandClear()
{
    std::cout << "\033[2J\033[1;1H";
}



std::ostream & operator<<(std::ostream & os, const Board & board)
{
    os << getFEN(board);
    return os;
}