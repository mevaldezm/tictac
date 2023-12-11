#include <string>
using namespace std;

#ifndef __TICTAC__
#define __TICTAC__

const size_t CELLS = 9;
const size_t ROWS  = 3;
const size_t COLS  = 3;

enum Mark
{
    EMPTY,
    NOUGHT = 79, //ASCII O
    CROSS  = 88  //ASCII X
};
enum Winner
{
    NONE,
    GAME,
    USER
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
    size_t GetRow(char);

public:
    TicTac();
    void Play();
    bool Play(const string &);
    void SetMarks(char);
    Mark GetUserMark();
    Winner CheckWinner();
    void Reset();
    void Print();
    void Wait(int sec);
};

void menu(UserOptions &);
void play(const UserOptions &);
void bye();

#endif __TICTAC__
