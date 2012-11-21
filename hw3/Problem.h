#ifndef _PROBLEM_H_
#define _PROBLEM_H_


#include "hw2_include.h"

namespace csci561
{

class Problem;
class Action
{
    public:
    Action(int x, int y, char color) 
    {
        _x = x;
        _y = y;
        _color = color;
    }
    Action() {}

    ~Action() {}

        int _x;
        int _y;
        char _color;
};

class Board
{
    public:
    Board(int size, char ** data);
    ~Board();

    int countChar(char color);
    int getRedCnt();
    int getGoldCnt();
    int getRedScore();
    int getGoldScore();
    int getScore(char color);
    int getContinueCnt(int x, int y, bool ** &visited);
    int getHeu(Action act);
    int getHeuVal(Action &act, bool ** &visited);
    int getHeuVal2(Action &act);
    int getSize() {return _size;}
    int getSizeSq() {return _size * _size;}
    bool ** getArray();

   
        friend class Problem;

        int _size;
        char **_data;
};

class Problem
{
    public:
        Problem(Board * state);
        ~Problem();

        /*
         * terminal or not
         */
        bool isTerm(Board *state);
        /*
         * who should do the next move in current state
         */
        char getPlayer(Board *state);
        /*
         * when meet terminal, get the utility
         * note that state must be terminal state
         */
        int getUtil(Board *state, char color);
        /*
         * when reach the depth limit, use heuristic function
         */
        int getHeUtil(Board *state, char color);
        /*
         * valid actions in current state
         */
        int getActions(Board *state, std::vector<Action> &act);
        /*
         * do the action, get a new state
         */
        int doAct(Board *cur, Board **next, Action &act);
        void clearMember();

    public:
        Board *_init_state;
        char _init_c;
        char _counter_c;

};

} //namespace csci561

#endif
