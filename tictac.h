#include <string>
#ifndef __TICTAC__
#define __TICTAC__

const short CELLS = 9;
const short ROWS = 3;
const short COLS = 3;

enum Mark
{
    EMPTY = 32,  // ASCII SPACE
    NOUGHT = 79, // ASCII O
    CROSS = 88   // ASCII X
};
enum Winner
{
    NONE,
    GAME,
    USER,
    DRAW
};
struct UserOptions
{
    char user_mark;
    char game_starter;
};

class TicTac
{
private:
    Mark grid[ROWS][COLS];
    const char rows[ROWS] = {'A', 'B', 'C'};
    Mark user_mark;
    Mark game_mark;
    Winner MarkToWinner(Mark) const;
    short GetRow(char) const;

public:
    TicTac();
    bool Play();
    bool Play(const std::string &);
    void SetMarks(char);
    Winner CheckWinner() const;
    bool PlayMark(Mark, Mark);
    void Reset();
    void Print() const;
    void Wait(int sec) const;
};

void menu(UserOptions &);
void play(const UserOptions &);
void bye();
void die(int);

#endif