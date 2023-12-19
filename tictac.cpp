#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include "tictac.h"

using namespace std;


TicTac::TicTac()
{
    for (short n{}; n < ROWS; ++n)
        for (short m{}; m < COLS; ++m)
            grid[n][m] = EMPTY;
}

bool TicTac::Play()
{
    if (playMark(gameMark, gameMark) || playMark(userMark, gameMark))
        return true;

    int count = 0;

    srand((unsigned)time(NULL));

    while (count < CELLS)
    {
        short row = rand() % ROWS;
        short col = rand() % COLS;
        Mark value = grid[row][col];

        if (value == EMPTY)
        {
            grid[row][col] = gameMark;
            return true;
        }
        count++;
    }
    return false;
}

bool TicTac::Play(const string &cell)
{
    short col = getCol(toupper(cell[0]));
    short row = atoi(cell.substr(1).c_str());

    row--; // matrix row

    if ((col < 0 || col > 2) || (row < 0 || row > 2))
        return false;

    Mark mark = grid[row][col];

    if (mark == EMPTY)
    {
        grid[row][col] = userMark;
        return true;
    }

    return false;
}

void TicTac::SetMarks(char mark)
{
    userMark = (Mark)toupper(mark);
    gameMark = userMark == NOUGHT ? CROSS : NOUGHT;
}

Winner TicTac::CheckWinner() const
{
    int count{};

    // check rows
    for (short n{}; n < ROWS; n++)
        if (grid[n][0] == grid[n][1] && grid[n][0] == grid[n][2])
            return markToWinner(grid[n][0]);

    // check columns
    for (short n{}; n < COLS; n++)
        if (grid[0][n] == grid[1][n] && grid[0][n] == grid[2][n])
            return markToWinner(grid[0][n]);

    // check diagonal
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
        return markToWinner(grid[0][0]);

    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
        return markToWinner(grid[0][2]);

    for (short n{}; n < ROWS; ++n)
        for (short m{}; m < COLS; ++m)
            if (grid[n][m] != EMPTY)
                count++;

    if (count == CELLS)
        return DRAW;

    return NONE;
}

/// @brief Search for a contigous game mark to place mark to win block opponent
/// @param smark game mark to search on grid
/// @param mark game mark to place on grid
/// @return true or false

bool TicTac::playMark(Mark smark, Mark mark)
{
    // Check rows
    for (short n{}; n < ROWS; n++)
    {
        if (grid[n][0] == smark && grid[n][1] == smark && grid[n][2] == EMPTY)
        {
            grid[n][2] = mark;
            return true;
        }
        else if (grid[n][0] == EMPTY && grid[n][1] == smark && grid[n][2] == smark)
        {
            grid[n][0] = mark;
            return true;
        }
        else if (grid[n][0] == smark && grid[n][1] == EMPTY && grid[n][2] == smark)
        {
            grid[n][1] = mark;
            return true;
        }
    } // for

    // check columns
    for (short n{}; n < COLS; n++)
    {
        if (grid[0][n] == smark && grid[1][n] == smark && grid[2][n] == EMPTY)
        {
            grid[2][n] = mark;
            return true;
        }
        else if (grid[0][n] == EMPTY && grid[1][n] == smark && grid[2][n] == smark)
        {
            grid[0][n] = mark;
            return true;
        }
        else if (grid[0][n] == smark && grid[1][n] == EMPTY && grid[2][n] == smark)
        {
            grid[1][n] = mark;
            return true;
        }
    } // for

    // check diagonal downward
    if (grid[0][0] == EMPTY && grid[1][1] == smark && grid[2][2] == smark)
    {
        grid[0][0] = mark;
        return true;
    }
    else if (grid[0][0] == smark && grid[1][1] == EMPTY && grid[2][2] == smark)
    {
        grid[1][1] = mark;
        return true;
    }
    else if (grid[0][0] == smark && grid[1][1] == smark && grid[2][2] == EMPTY)
    {
        grid[2][2] = mark;
        return true;
    }
	// check diagonal upward
	if (grid[2][0] == EMPTY && grid[1][1] == smark && grid[0][2] == smark)
    {
        grid[2][0] = mark;
        return true;
    }
    else if (grid[2][0] == smark && grid[1][1] == EMPTY && grid[0][2] == smark)
    {
        grid[1][1] = mark;
        return true;
    }
    else if (grid[2][0] == smark && grid[1][1] == smark && grid[0][2] == EMPTY)
    {
        grid[0][2] = mark;
        return true;
    }
    return false;
}

void TicTac::Reset()
{
    for (short n{}; n < ROWS; ++n)
        for (short m{}; m < COLS; ++m)
            grid[n][m] = EMPTY;
}

/// @brief Map winning mark on grip with its user
/// @param mark winning mark found on grid
/// @return Winner
Winner TicTac::markToWinner(Mark mark) const
{
    Winner winner = Winner::NONE;

    switch (mark)
    {
    case CROSS:
        winner = userMark == CROSS ? USER : GAME;
        break;
    case NOUGHT:
        winner = userMark == NOUGHT ? USER : GAME;
        break;
    case EMPTY:
        winner = NONE;
        break;
    default:
        break;
    }
    return winner;
}

short TicTac::getCol(char col) const
{
    for (short n{}; n < COLS; ++n)
        if (cols[n] == col)
            return n;
    return -1;
}

void TicTac::Print() const
{
    cout << endl;

    for (short i = 0; i < COLS; i++)
    {
        cout << "   " << cols[i] ;
    }
    cout << "\n---------------\n";

    for (short n{}; n < ROWS; ++n)
    {
		cout << n + 1 <<  " | ";
        for (short m{}; m < COLS; ++m)
            cout << (char)grid[n][m] << " | ";
        cout << endl;
    }
    cout << endl;
}

void bye()
{
    cout << "Thank you for playing" << endl;
    exit(0);
}
void die(int sig)
{
    cout << "Thank you for playing" << endl;
    exit(sig);
}

void menu(UserOptions &options)
{
    static size_t game_count = 0;
    //
    char choice = 'N';

    if (game_count > 0)
    {
        cout << "\nKeep playing, (Y, N)?: ";
        cin >> choice;
        choice = toupper(choice);
        cin.clear();
        if (choice != 'Y')
            bye();
    }

    game_count++;

    do
    {
        cout << "Choose a mark (X, O), (Q)uit ";
        cin >> options.userMark;
        options.userMark = toupper(options.userMark);
        cin.clear();

        if (options.userMark == 'Q')
        {
            bye();
        }

    } while (options.userMark != 'X' &&
             options.userMark != 'O' &&
             options.userMark != 'Q');
    //
    do
    {
        cout << "Choose (Y, N) for game stater, (Q)uit: ";
        cin >> options.gameStarter;
        options.gameStarter = toupper(options.gameStarter);
        cin.clear();

        if (options.gameStarter == 'Q')
        {
            bye();
        }

    } while (options.gameStarter != 'Y' &&
             options.gameStarter != 'N' &&
             options.userMark != 'Q');

} // menu

void play(const UserOptions &options)
{
    TicTac tic;
    string cell;

    if (options.userMark == 'X' || options.userMark == 'O')
    {
        tic.SetMarks(options.userMark);
    }

    if (options.gameStarter == 'N')
    {
        tic.Play();
    }

    tic.Print();

    for (short i = 0; i < CELLS; i++)
    {
        cout << "\nEnter a Cell (A1, B2,...), (Q)uit: ";
        cin >> cell;
        cin.clear();
        //
        if (cell == "Q" || cell == "q")
            bye();

        if (tic.Play(cell))
        {
            tic.Play();
            tic.Print();
        }
        else
            cout << "Wrong cell: " << cell << endl;

        Winner winner = tic.CheckWinner();

        if (winner == USER)
        {
            cout << "You won !!" << endl;
            break;
        }
        else if (winner == GAME)
        {
            cout << "Game won!!" << endl;
            break;
        }
        else if (winner == DRAW)
        {
            cout << "Game is tie." << endl;
            break;
        }

    } // for

    tic.Reset();
} // play
