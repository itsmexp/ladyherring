#include "CLI.h"
#include <iostream>

void printBoard(const Board &board)
{
    for(int i = 0; i < 64; i++)
    {
        if(i % 8 == 0)
            std::cout << std::endl;
        std::cout << "Hello World" << " ";
    }
    std::cout << std::endl;
}
