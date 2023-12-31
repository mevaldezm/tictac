#include <string>
#ifndef __TICTAC__
#define __TICTAC__

enum { CELLS = 9 };
enum { ROWS = 3 };
enum { COLS = 3 };

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
struct GameOptions
{
    char UserMark;
    char GameMark;
    char Starter;
};

class TicTac
{
private:
    Mark grid[ROWS][COLS];
    Mark userMark;
    Mark gameMark;
    Winner markToWinner(Mark) const;
	bool placeMark(Mark, Mark);
    
public:
    TicTac();
    bool Play();
    bool Play(std::string &);
    void SetMarks(char);
    Winner CheckWinner() const;
    void Reset();
    static std::string RightPad(std::string, char , short);
    void Print() const;
};

void bye();
void menu(GameOptions &);
void play(const GameOptions &);
#endif