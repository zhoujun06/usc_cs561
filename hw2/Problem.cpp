#include "Problem.h"

namespace csci561
{

    Problem::Problem()
    {}

    Problem::~Problem()
    {
    }

    void Problem::clearMember()
    {
        _size = 0;
        _obstacles.clear();
        _actions.clear();
        _act_cost.clear();
    }

    bool Problem::isGoal(MapNode *node) 
    {
        return (node->getNodeA().getX() == node->getNodeB().getX()) && 
            (node->getNodeA().getY() == node->getNodeB().getY());
    }

    int Problem::getSize() 
    {
        return _size;
    }

    void Problem::setSize(int size)
    {
        _size = size;
    }

    MapNode * Problem::getInitState()
    {
        return _init_state;
    }

    void Problem::setInitState(int x1, int y1, int x2, int y2)
    {
        _init_state = new MapNode(x1, y1, x2, y2, NULL, MOV_ACT_NOOP, 0);
    }

    void Problem::setObstacles(std::vector<Node> &obs)
    {
        std::vector<Node>::iterator it;
        for(it = obs.begin(); it < obs.end(); it++)
        {
            _obstacles.insert(it->getKey());
        }
    }

    bool Problem::isObstacle(int x, int y)
    {
        Node node = Node(x, y);
        return _obstacles.find(node.getKey()) != _obstacles.end();
    }

    std::vector<MovAction_t> & Problem::getActions() 
    {
        return _actions;
    }

    void Problem::setActions(int ctop, int cright, int cdown, int cleft)
    {
        _actions.push_back(MOV_ACT_TOP);
        _actions.push_back(MOV_ACT_RIGHT);
        _actions.push_back(MOV_ACT_DOWN);
        _actions.push_back(MOV_ACT_LEFT);

        _act_cost.insert(std::pair<MovAction_t, int>(MOV_ACT_TOP, ctop));
        _act_cost.insert(std::pair<MovAction_t, int>(MOV_ACT_RIGHT, cright));
        _act_cost.insert(std::pair<MovAction_t, int>(MOV_ACT_DOWN, cdown));
        _act_cost.insert(std::pair<MovAction_t, int>(MOV_ACT_LEFT, cleft));
    }

    int Problem::getActCost(MovAction_t act)
    {
        return _act_cost.find(act)->second;
    }

    int Problem::movAction(MapNode *cur, MovAction_t action, MapNode **next)
    {
        int x1, x2, y1, y2 = 0;

        switch(action)
        {
            case MOV_ACT_RIGHT:
                x1 = cur->getNodeA().getX() + 1;
                y1 = cur->getNodeA().getY();
                x2 = cur->getNodeB().getX();
                y2 = cur->getNodeB().getY() + 1;
                break;

            case MOV_ACT_DOWN:
                x1 = cur->getNodeA().getX();
                y1 = cur->getNodeA().getY() + 1;
                x2 = cur->getNodeB().getX() - 1;
                y2 = cur->getNodeB().getY();
                break;

            case MOV_ACT_LEFT:
                x1 = cur->getNodeA().getX() - 1;
                y1 = cur->getNodeA().getY();
                x2 = cur->getNodeB().getX();
                y2 = cur->getNodeB().getY() - 1;
                break;

            case MOV_ACT_TOP:
                x1 = cur->getNodeA().getX();
                y1 = cur->getNodeA().getY() - 1;
                x2 = cur->getNodeB().getX() + 1;
                y2 = cur->getNodeB().getY();
                break;

            default:
                break;
        }

        if(x1 < 1 || x2 < 1 || x1 > _size || x2 > _size ||
           y1 < 1 || y2 < 1 || y1 > _size || y2 > _size) 
        {
            return NO_OP;
        }

        if(isObstacle(x1, y1) || isObstacle(x2, y2))
        {
            return NO_OP;
        }


        int cost = cur->getPathCost() + getActCost(action);
        *next = new MapNode(x1, y1, x2, y2, cur, action, cost);

        return OP_OK;
    }

} //namespace
