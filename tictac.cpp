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
    for (size_t n{}; n < ROWS; ++n)
        for (size_t m{}; m < COLS; ++m)
            grid[n][m] = EMPTY;
}

void TicTac::Wait(int sec)
{
    // time_t end = time(NULL) * sec;
    // while( time(NULL) < end ) ;

    // window only
    Sleep(1000 * sec);
}
void TicTac::Play()
{
    int count = 0;
    srand((unsigned int)time(NULL));

    while (count < CELLS)
    {
        size_t row = rand() % ROWS;
        size_t col = rand() % COLS;
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
    size_t row = GetRow(toupper(coord[0]));
    size_t col = atoi(coord.substr(1).c_str());

    col--; // matrix column

    if ((col < 0 || col > 2) || (row < 0 || row > 2))
        return false;

    Mark value = grid[row][col];

    if (value == EMPTY)
    {
        grid[row][col] = user_mark;
        return true;
    }
    return false;
}

void TicTac::SetMarks(char mark)
{
    user_mark = (Mark)toupper(mark);
    game_mark = user_mark == NOUGHT ? CROSS : NOUGHT;
}

Mark TicTac::GetUserMark()
{
    return user_mark;
}

Winner TicTac::CheckWinner()
{
    int count{};

    // check rows
    for (size_t n{}; n < ROWS; n++)
        if (grid[n][0] == grid[n][1] && grid[n][0] == grid[n][2])
            return MarkToWinner(grid[n][0]);

    // check columns
    for (size_t n{}; n < COLS; n++)
        if (grid[0][n] == grid[1][n] && grid[0][n] == grid[2][n])
            return MarkToWinner(grid[0][n]);

    // check diagonal
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
        return MarkToWinner(grid[0][0]);

    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
        return MarkToWinner(grid[0][2]);

    for (size_t n{}; n < ROWS; ++n)
        for (size_t m{}; m < COLS; ++m)
            if (grid[n][m] != EMPTY)
                count++;

    if (count == CELLS)
        return DRAW;

    return NONE;
}

void TicTac::Reset()
{
    for (size_t n{}; n < ROWS; ++n)
        for (size_t m{}; m < COLS; ++m)
            grid[n][m] = EMPTY;
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

size_t TicTac::GetRow(char row)
{
    for (size_t n{}; n < ROWS; ++n)
        if (rows[n] == row)
            return n;
    return -1;
}

void TicTac::Print()
{
    for (size_t i = 0; i < COLS; i++)
    {
        cout << setw(3) << " " << i + 1 << " ";
    }
    cout << "\n------------------\n";

    for (size_t n{}; n < ROWS; ++n)
    {
        cout << rows[n] << " | ";
        for (size_t m{}; m < COLS; ++m)
            cout << (char)grid[n][m] << " | ";
        cout << endl;
    }
}

void bye()
{
    cout << "Thank you for playing" << endl;
    exit(0);
}

void menu(UserOptions &options)
{
    static size_t count = 0;
    char choice = 'N';

    if (count > 0)
    {
        cout << "Would you like to continue Y, N?";
        cin >> choice;
        choice = toupper(choice);
        cin.clear();
        if (choice != 'Y')
            bye();
    }

    count++;

    do
    {
        cout << "Please choose X, O for game mark or Q to quit: ";
        cin >> options.user_mark;
        options.user_mark = toupper(options.user_mark);
        cin.clear();

        if (options.user_mark == 'Q')
            bye();

    } while (options.user_mark != 'X' &&
             options.user_mark != 'O' &&
             options.user_mark != 'Q');
    //
    cout << "Please choose Y, N for the game stater, Q to quit: ";
    cin >> options.game_starter;
    //
    options.game_starter = toupper(options.game_starter);
    cin.clear();

    if (options.game_starter == 'Q')
        bye();
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

    for (size_t i = 0; i < CELLS; i++)
    {
        cout << "\nEnter a cell [A2, B1, C3, etc.], or Q to quit: ";
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
            cout << uppercase << cell << " is not a valid cell. Please try again." << endl;

        Winner winner = tic.CheckWinner();

        if (winner == USER)
        {
            cout << "You won !!" << endl;
        }
        else if (winner == GAME)
        {
            cout << "Game won!!" << endl;
        }
        else if (winner == DRAW)
        {
            cout << "Game ended tie." << endl;
            break;
        } 
        

    } // for

    tic.Reset();
}
