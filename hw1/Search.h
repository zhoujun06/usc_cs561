#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "hw1_include.h"
#include "MapNode.h"
#include "Queue.h"
#include "Problem.h"

namespace csci561
{

class Search
{
public:
    ~Search();


    void insertQueue(MapNode *node);
    MapNode * getFromQueue();
    bool isInQueue(MapNode *node);
    void insertExplored(MapNode *node);
    bool isInExplored(MapNode *node);
    virtual bool doSearch(Problem &problem, std::vector<MapNode*> &path);

    int getExploredSize()
    {
        return _explored.size();
    }

    int getStoredSize()
    {
        return _stored.size();
    }

public:
    Queue<MapNode *> *_queue;

    /*
     * we use the x and y of the node to construct the key of the map
     * key = 10*x + y
     */
    std::map<int, MapNode *> _explored;

    //stored for easy find in queue
    std::map<int, MapNode *> _stored;
};

class BFSearch : public Search
{
public:
    BFSearch()
    {
        _queue = new FIFOQueue<MapNode *>();
    }

    ~BFSearch()
    {
        while(!_queue->isEmpty())
        {
            delete _queue->pop();
        }
        delete _queue;
    }

    bool doSearch(Problem &problem, std::vector<MapNode *> &path);


};


class UCSearch : public Search
{
public:
    UCSearch()
    {
        _queue = new PrioQueue<MapNode *>;
    }

    ~UCSearch()
    {
        while(!_queue->isEmpty())
        {
            delete _queue->pop();
        }
        delete _queue;
    }

    bool doSearch(Problem &problem, std::vector<MapNode *> &path);
    MapNode *findQueueByKey(int key);
    void updateQueue(MapNode *old_node, MapNode *new_node);

};

} //namespace

#endif
