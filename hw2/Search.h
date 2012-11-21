#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "hw2_include.h"
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
    MapNode *findQueueByKey(int key);
    void updateQueue(MapNode *old_node, MapNode *new_node);
    void traceNode(MapNode *node);

    virtual bool doSearch(Problem &problem, std::vector<MapNode*> &path);

    int getExploredSize()
    {
        return _explored.size();
    }

    int getStoredSize()
    {
        return _stored.size();
    }

    void clearMember()
    {
        if (_queue != NULL)
            _queue->clear();
        _explored.clear();
        _stored.clear();
    }

    const char *getName()
    {
        return _name;
    }
public:
    //just for use of debug
    const char *_name;

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


class PrioSearch : public Search
{
public:
    PrioSearch(const char *name, DistType_t dtype)
    {
        _name = name;
        switch (dtype) {
//            case DIST_UCS:
//                _queue = new PrioQueue<MapNode *>;
//                break;
            case DIST_EUC:
                _queue = new EucQueue<MapNode *>;
                break;
            case DIST_MAN:
                _queue = new ManQueue<MapNode *>;
                break;
            case DIST_CHE:
                _queue = new CheQueue<MapNode *>;
                break;
            case DIST_GREEDY_MAN:
                _queue = new GreedyManQueue<MapNode *>;
                break;
        }
    }

    ~PrioSearch()
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
//    MapNode *findQueueByKey(int key);
//    void updateQueue(MapNode *old_node, MapNode *new_node);

};


} //namespace

#endif
