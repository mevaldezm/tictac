#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <windows.h>
#include "tictac.h"
using namespace std;

TicTac::TicTac()
{
    for (short n{}; n < ROWS; ++n)
        for (short m{}; m < COLS; ++m)
            grid[n][m] = EMPTY;
    play_count = 0;
}

void TicTac::Wait(int sec)
{
    // time_t end = time(NULL) * sec;
    // while( time(NULL) < end ) ;
    Sleep(1000 * sec);
}
void TicTac::Play()
{
    int count = 0;
    srand((unsigned int)time(NULL));

    while (count < CELLS)
    {
        short row = rand() % ROWS;
        short col = rand() % COLS;
        Mark value = grid[row][col];

        if (value == EMPTY)
        {
            grid[row][col] = game_mark;
            break;
        }
        count++;
    }
}

bool TicTac::Play(const string &coord)
{
    short row = GetRow(toupper(coord[0]));
    short col = atoi(coord.substr(1).c_str());

    col--; // matrix column

    if ((col < 0 || col > 2) || (row < 0 || row > 2))
        return false;

    Mark value = grid[row][col];

    if (value == EMPTY)
    {
        grid[row][col] = user_mark;
        return true;
    }

    play_count++;

    return false;
}

void TicTac::SetMarks(char mark)
{
    user_mark = (Mark)toupper(mark);
    game_mark = user_mark == NOUGHT ? CROSS : NOUGHT;
}

Winner TicTac::CheckWinner()
{
    int count{};

    // check rows
    for (short n{}; n < ROWS; n++)
        if (grid[n][0] == grid[n][1] && grid[n][0] == grid[n][2])
            return MarkToWinner(grid[n][0]);

    // check columns
    for (short n{}; n < COLS; n++)
        if (grid[0][n] == grid[1][n] && grid[0][n] == grid[2][n])
            return MarkToWinner(grid[0][n]);

    // check diagonal
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
        return MarkToWinner(grid[0][0]);

    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
        return MarkToWinner(grid[0][2]);

    for (short n{}; n < ROWS; ++n)
        for (short m{}; m < COLS; ++m)
            if (grid[n][m] != EMPTY)
                count++;

    if (count == CELLS)
        return DRAW;

    return NONE;
}

void TicTac::Reset()
{
    for (short n{}; n < ROWS; ++n)
        for (short m{}; m < COLS; ++m)
            grid[n][m] = EMPTY;
    play_count = 0;
}

Winner TicTac::MarkToWinner(Mark mark)
{
    Winner winner = Winner::NONE;

    switch (mark)
    {
    case CROSS:
        winner = user_mark == CROSS ? USER : GAME;
        break;
    case NOUGHT:
        winner = user_mark == NOUGHT ? USER : GAME;
        break;
    case EMPTY:
        winner = NONE;
        break;
    default:
        break;
    }
    return winner;
}

short TicTac::GetRow(char row)
{
    for (short n{}; n < ROWS; ++n)
        if (rows[n] == row)
            return n;
    return -1;
}

void TicTac::Print()
{
    cout << endl;

    for (short i = 0; i < COLS; i++)
    {
        cout << setw(3) << " " << i + 1 << " ";
    }
    cout << "\n------------------\n";

    for (short n{}; n < ROWS; ++n)
    {
        cout << rows[n] << " | ";
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

void menu(UserOptions &options)
{
    static short game_count = 0;
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
        cin >> options.user_mark;
        options.user_mark = toupper(options.user_mark);
        cin.clear();

        if (options.user_mark == 'Q')
        {
            bye();
        }

    } while (options.user_mark != 'X' &&
             options.user_mark != 'O' &&
             options.user_mark != 'Q');
    //
    cout << "Choose (Y, N) for game stater, (Q)uit: ";
    cin >> options.game_starter;
    //
    options.game_starter = toupper(options.game_starter);
    cin.clear();

    if (options.game_starter == 'Q')
    {
        bye();
    }
}

void play(const UserOptions &options)
{
    TicTac tic;
    string cell;

    switch (options.user_mark)
    {
    case 'X':
    case 'O':
        tic.SetMarks(options.user_mark);
        break;
    default:
        break;
    }
    switch (options.game_starter)
    {
    case 'N':
        tic.Play();
        break;
    default:
        break;
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
            cout << "Invalid cell: " << cell << ". Try again." << endl;

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
            cout << "Game ended tie." << endl;
            break;
        }

    } // for

    tic.Reset();
}
