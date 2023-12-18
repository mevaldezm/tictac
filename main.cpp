#include "tictac.h"
#include <csignal>
#include <iostream>
using namespace std;

int main()
{

   UserOptions options;

    while (true)
    {
        menu(options);
        play(options);

    } // while
}
