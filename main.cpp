#include "tictac.h"

int main()
{

   GameOptions options;

    while (true)
    {
        menu(options);
        play(options);

    } // while
	
	return 0;
}
