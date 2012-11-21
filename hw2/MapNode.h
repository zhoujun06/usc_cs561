#ifndef _NODE_H_
#define _NODE_H_

#include "hw2_include.h"

namespace csci561
{

class MapNode;
class Node
{       
    public:
        Node(int x, int y)
        {
            _x = x;
            _y = y;
        }

        Node()
        {
            _x = 0;
            _y = 0;
        }

        int getX() const
        {
            return _x;
        }

        int getY() const
        {
            return _y;
        }

        int getKey() const
        {
            return _x * 10 + _y;
        }

    private:
        friend class MapNode;
        int _x;
        int _y;
};

class MapNode
{
    public:
        MapNode(int x1, int y1, int x2, int y2, MapNode *parent, MovAction_t act, int cost)
        {
            _node_a = Node(x1, y1);
            _node_b = Node(x2, y2);
            _parent = parent;
            _act = act;
            _path_cost = cost;
        }

        MapNode()
        {
            _node_a = Node();
            _node_b = Node();
        }

        int getPathCost() const
        {
            return _path_cost;
        }

        void setPathCost(int cost)
        {
            _path_cost = cost;
        }

        MapNode *getParent() const
        {
            return _parent;
        }

        Node getNodeA() const
        {
            return _node_a;
        }

        Node getNodeB() const
        {
            return _node_b;
        }

        int getKey() const
        {
            return _node_a.getKey();
        }

        void getPathFromRoot(std::vector<MapNode *> &path);

#ifdef EUC_INTEGER
        int getEucDist() const
        {
            int diffx = std::abs(_node_a._x - _node_b._x);
            int diffy = std::abs(_node_a._y - _node_b._y);
            int dist = std::sqrt(diffx * diffx + diffy * diffy);

            return _path_cost + dist * 2;
        }
#else
        double getEucDist() const
        {
            double diffx = std::abs(_node_a._x - _node_b._x);
            double diffy = std::abs(_node_a._y - _node_b._y);
            double dist = std::sqrt(diffx * diffx + diffy * diffy);

            return _path_cost + dist * 2;
        }
#endif

        int getManDist() const
        {
            int diffx = std::abs(_node_a._x - _node_b._x);
            int diffy = std::abs(_node_a._y - _node_b._y);
            int dist = diffx + diffy;

            return _path_cost + dist * 2;
        }

        int getGreedyManDist() const
        {
            int diffx = std::abs(_node_a._x - _node_b._x);
            int diffy = std::abs(_node_a._y - _node_b._y);
            int dist = diffx + diffy;

            return dist * 2;
        }

        int getCheDist() const
        {
            int diffx = std::abs(_node_a._x - _node_b._x);
            int diffy = std::abs(_node_a._y - _node_b._y);
            int dist = diffx > diffy ? diffx : diffy;
            
            return _path_cost + dist * 2;
        }

    private:
        Node _node_a;
        Node _node_b;

        MapNode * _parent;
        MovAction_t _act;

        int _path_cost;
};

}  //namespace csci561


#endif
