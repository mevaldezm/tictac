#include <string>
using namespace std;

#ifndef __TICTAC__
#define __TICTAC__

const short CELLS = 9;
const short ROWS = 3;
const short COLS = 3;

enum Mark
{
    EMPTY = 32,  // SPACE
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
    char rows[ROWS] = {'A', 'B', 'C'};
    Mark user_mark;
    Mark game_mark;
    Winner MarkToWinner(Mark);
    short GetRow(char);
    short play_count;

public:
    TicTac();
    void Play();
    bool Play(const string &);
    void SetMarks(char);
    Winner CheckWinner();
    short GetPlayCount() const { return play_count; }
    void ResetPlayCount() { play_count = 0; }
    void Reset();
    void Print();
    void Wait(int sec);
};

void menu(UserOptions &);
void play(const UserOptions &);
void bye();

#endif __TICTAC__
