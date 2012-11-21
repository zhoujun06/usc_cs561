#ifndef _PROBLEM_H_
#define _PROBLEM_H_


#include "hw1_include.h"
#include "MapNode.h"

namespace csci561
{

class Problem
{
    public:
        Problem();
        ~Problem();

        bool isGoal(MapNode *node);
        int getSize();
        void setSize(int size);
        MapNode * getInitState();
        void setInitState(int x1, int y1, int x2, int y2);
        void setObstacles(std::vector<Node> &obs);
        void setActions(int top, int right, int down, int left);
        int getActCost(MovAction_t act);

        bool isObstacle(int x, int y);
        int movAction(MapNode *cur, MovAction_t action, MapNode **next);
        std::vector<MovAction_t> & getActions();
   
    private:
        int _size;
        MapNode * _init_state;
        std::set<int> _obstacles;

        std::vector<MovAction_t> _actions;
        std::map<MovAction_t, int> _act_cost;
};

} //namespace csci561

#endif
