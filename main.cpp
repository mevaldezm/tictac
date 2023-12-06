#include "tictac.h"
using namespace std;

int main(int argc, char const *argv[])
{
    UserOptions options;

    while (true)
    {
        menu(options);
        play(options);

    } // while

    return EXIT_SUCCESS;
}
