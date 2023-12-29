#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "tictac.h"

TicTac::TicTac()
{
    for (short n{}; n < ROWS; ++n)
        for (short m{}; m < COLS; ++m)
            grid[n][m] = EMPTY;
}

bool TicTac::Play()
{
    // Try to win first, otherwise try to block opponent
    if (placeMark(gameMark, gameMark) || placeMark(userMark, gameMark))
        return true;

    int count = 0;

    srand((unsigned)time(NULL));

    while (count < CELLS)
    {
        short row = rand() % ROWS;
        short col = rand() % COLS;
        Mark mark = grid[row][col];

        if (mark == EMPTY)
        {
            grid[row][col] = gameMark;
            return true;
        }
        count++;
    }
    return false;
}

bool TicTac::Play(std::string &cell)
{
    short col = toupper(cell[0]) - 'A'; // to col position: A-A = 0, B-A = 1
    short row = cell[1] - '0';          // ascii number to an int

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

    // check diagonals
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

/// @brief Search for a contigous game mark to place a mark to win block opponent
/// @param smark game mark to search on grid
/// @param mark game mark to place on grid
/// @return true or false

bool TicTac::placeMark(Mark smark, Mark mark)
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

void TicTac::Print() const
{
    std::cout << std::endl;

    for (char c = 'A'; c < COLS + 'A'; c++)
    {
        std::cout << "   " << c;
    }
    std::cout << "\n---------------\n";

    for (short r{}; r < ROWS; ++r)
    {
        std::cout << r + 1 << " | ";
        for (short c{}; c < COLS; ++c)
            std::cout << (char)grid[r][c] << " | ";
        std::cout << std::endl;
    }
    std::cout << "---------------\n";
    
}

void bye()
{
    std::cout << "Thank you for playing" << std::endl;
    exit(0);
}

void menu(GameOptions &options)
{
    static size_t game_count = 0;
    //
    char choice = 'N';

    if (game_count > 0)
    {
        std::cout << "\nKeep playing, (Y, N)?: ";
        std::cin >> choice;
        choice = toupper(choice);
        std::cin.clear();
        if (choice != 'Y')
            bye();
    }

    game_count++;
    std::cout << "Enter (Q) at any prompt to quit" << std::endl;

    do
    {
        std::cout << "Enter a mark (X, O): ";
        std::cin >> options.UserMark;
        options.UserMark = toupper(options.UserMark);
        std::cin.clear();

        if (options.UserMark == 'Q')
        {
            bye();
        }

    } while (options.UserMark != 'X' &&
             options.UserMark != 'O' &&
             options.UserMark != 'Q');
    //
    do
    {
        std::cout << "Enter (Y) to play first, (N) for computer: ";
        std::cin >> options.Starter;
        options.Starter = toupper(options.Starter);
        std::cin.clear();

        if (options.Starter == 'Q')
        {
            bye();
        }

    } while (options.Starter != 'Y' &&
             options.Starter != 'N' &&
             options.UserMark != 'Q');

} // menu

void play(const GameOptions &options)
{
    TicTac tic;
    std::string cell;
    Winner winner = NONE;
    tic.SetMarks(options.UserMark);

    if (options.Starter == 'N')
    {
        tic.Play();
    }

    tic.Print();

    for (short i = 0; i < CELLS; i++)
    {

        std::cout << "\nEnter a cell (A1, B2,...): ";
        std::cin >> cell;
        std::cin.clear();
        //
        if (cell == "Q" || cell == "q")
            bye();

        if (tic.Play(cell))
        {
            winner = tic.CheckWinner();

            if (winner == NONE)
            {
                tic.Play();
                winner = tic.CheckWinner();
            }
            tic.Print();

            if (winner == USER)
            {
                std::cout << "You won !!" << std::endl;
                return;
            }
            else if (winner == GAME)
            {
                std::cout << "Game won!!" << std::endl;
                return;
            }
            else if (winner == DRAW)
            {
                std::cout << "Draw. Neither won !!" << std::endl;
                return;
            }
        }
        else
        {
            std::cout << "You entered a wrong cell: " << cell << std::endl;
            i--;
        }

    } // for

    tic.Reset();
} // play
