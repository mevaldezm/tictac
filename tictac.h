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
    char userMark;
    char gameStarter;
};

class TicTac
{
private:
    Mark grid[ROWS][COLS];
    const char cols[COLS] = {'A', 'B', 'C'};
    Mark userMark;
    Mark gameMark;
    Winner markToWinner(Mark) const;
	bool playMark(Mark, Mark);
    short getCol(char) const;

public:
    TicTac();
    bool Play();
    bool Play(const std::string &);
    void SetMarks(char);
    Winner CheckWinner() const;
    void Reset();
    void Print() const;
};

void menu(UserOptions &);
void play(const UserOptions &);
void bye();

#endif