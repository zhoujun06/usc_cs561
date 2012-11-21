#include "Search.h"

namespace csci561
{


Search::~Search()
{ 
    std::map<int, MapNode *>::iterator it;
    for(it = _explored.begin(); it != _explored.end(); it++)
    {
        delete it->second;
        it->second = NULL;
    }

    _explored.clear();
    _stored.clear();
}

#if 1
/*
 * search algorithm according to the text book
 * initialize the queue with the initial state of the problem
 * initialize the explored set to be empty
 * loop do
 *      if the queue is empty, return failure
 *      choose a leaf node, remove it from the queue
 *      if the node is goal, then return the solution
 *      else add the node to explored set
 *      expand the node, and add the result nodes to the queue and 
 *      explored set, only when it is not in the explored set
 */
bool Search::doSearch(Problem &problem, std::vector<MapNode *> &path)
{
    return true;
}

void Search::traceNode(MapNode *node)
{
#ifdef HW2_DEBUG
    std::cout << "\tA x: " << node->getNodeA().getX();
    std::cout << "\tA y: " << node->getNodeA().getY();
    std::cout << "\tB x: " << node->getNodeB().getX();
    std::cout << "\tB y: " << node->getNodeB().getY();
    std::cout << std::endl;
#endif
}

void Search::insertQueue(MapNode *node)
{
    _queue->push(node);

    int key = node->getKey();
    _stored.insert(std::pair<int, MapNode *>(key, node));
}

MapNode * Search::getFromQueue()
{
    MapNode * node = _queue->pop();
    int key = node->getKey();

    std::map<int, MapNode *>::iterator it;
    it = _stored.find(key);
    _stored.erase(it);

    return node;
}

MapNode * Search::findQueueByKey(int key)
{
    std::map<int, MapNode *>::iterator it;
    it = _stored.find(key);
    if(it != _stored.end())
    {
        return it->second;
    }

    return NULL;
}

void Search::updateQueue(MapNode *old_node, MapNode *new_node)
{
    //what we have is the pointer to the old_node in the map, 
    //since we cant access a particular node in the priority queue
    //so we cant update the pointer in the queue to pointer to new old
    //thus we do it with a tricky method:
    //we memcpy the contents of new_node to the address of the old one
    //then, although the ptr in the queue is not changed, although it 
    //still points to the old node, but ,actually, it has the contens of 
    //the new node, and then, we just delete the new_node, in case of 
    //memory leak.
    //Since it is in the queue, not explored yet, so no child will point to
    //the old one, thus the memcpy won't bring other by products.
    memcpy(old_node, new_node, sizeof(MapNode));

    delete new_node;
    new_node = NULL;
}

bool Search::isInQueue(MapNode *node)
{
    int key = node->getKey();
    if(_stored.find(key) != _stored.end())
    {
        return true;
    }

    return false;
}

void Search::insertExplored(MapNode *node)
{       
    int key = node->getKey();
    _explored.insert(std::pair<int, MapNode *>(key, node));
}

bool Search::isInExplored(MapNode *node)
{
    int key = node->getKey();
    if(_explored.find(key) != _explored.end())
    {
        return true;
    }

    return false;
}

/*
 * test the initial state is goal or not
 * if not, put it in the queue, and initialize the explored set to be empty
 * loop do
 *      if queue is empty, return failure
 *      pop one node from the queue, add it to the explored set
 *      for each action in Problem.Action(node.state) do
 *          get a child node by doing: Action(problem, node)
 *          if child node is not in queue of explored set
 *              if the child node is goal, return the solution,
 *              other wise add the child node in the queue
 *
 */


bool BFSearch::doSearch(Problem &problem, std::vector<MapNode *> &path)
{
    clearMember();
    MapNode *init = problem.getInitState();
    if(problem.isGoal(init))
    {
        init->getPathFromRoot(path); 
        return true;
    }

    insertQueue(init);

    while(!_queue->isEmpty())
    {
        MapNode * node = getFromQueue();
        insertExplored(node);
        traceNode(node);

        std::vector<MovAction_t> & actions = problem.getActions();
        std::vector<MovAction_t>::iterator it;
        for(it = actions.begin(); it < actions.end(); it++)
        {
            if(*it == MOV_ACT_NOOP) 
            {
                continue;
            }

            MapNode * child = NULL;
            int res = 0;
            res = problem.movAction(node, *it, &child);
            if(res == OP_OK)
            {
                //check if in the queue
                if(!isInQueue(child) && !isInExplored(child))
                {
                    if(problem.isGoal(child))
                    {
                        child->getPathFromRoot(path);
                        return true;
                    }

                    insertQueue(child);
                }
            }
        } //for
    } //while
     
    return false;
}


/*
 * initialize the priority queue with the initial state
 * explored <-- empty
 * loop do
 *      if empty(queue) return failure
 *      node <-- queue.pop()
 *      if node is goal, then return solution(node)
 *      add node to explored
 *      for each action in Action(problem, node) do
 *          child node <-- childnode(problem, node, action)
 *          if child is not in queue or expolored, add node to queue
 *          otherwise, if the child.state is in queue and with a higher pathcost,
 *          then replace that node with the child
 *
 */
bool UCSearch::doSearch(Problem &problem, std::vector<MapNode *> &path)
{
    clearMember();
    MapNode *init = problem.getInitState();
    insertQueue(init);

    while(!_queue->isEmpty())
    {
        MapNode *node = _queue->pop();
        if(problem.isGoal(node))
        {
            node->getPathFromRoot(path);
            return true;
        }
        
        insertExplored(node);
        traceNode(node);
        
        std::vector<MovAction_t> & action = problem.getActions();
        std::vector<MovAction_t>::iterator it;
        for(it=action.begin(); it<action.end(); it++)
        {
            if(*it == MOV_ACT_NOOP) {
                continue;
            }

            MapNode *child = NULL;
            int res = 0;
            res = problem.movAction(node, *it, &child);
            if(res == OP_OK)
            {
                if(!isInQueue(child) && !isInExplored(child))
                {
                    insertQueue(child);
                }
                else
                {
                    if(isInQueue(child))
                    {
                        //get old one
                        MapNode *old = findQueueByKey(child->getKey());
                        if(child->getPathCost() < old->getPathCost())
                        {
                            //update;
#ifdef HW2_DEBUG
                            std::cout <<"before update, child cost: " << child->getPathCost();
                            std::cout <<",  old cost: " << old->getPathCost();
#endif
                            updateQueue(old, child);
#ifdef HW2_DEBUG
                            std::cout <<"after,  old cost: " << old->getPathCost();
#endif
                        }
                    }
                }
            }
        }
    }

    return false;
}

bool PrioSearch::doSearch(Problem &problem, std::vector<MapNode *> &path)
{
#ifdef HW2_DEBUG
        std::cout << _name << " start\n";
#endif
    clearMember();
    MapNode *init = problem.getInitState();
    insertQueue(init);

    while(!_queue->isEmpty())
    {
        MapNode *node = _queue->pop();
        if(problem.isGoal(node))
        {
            node->getPathFromRoot(path);
            return true;
        }
        
        insertExplored(node);
        traceNode(node);
        
        std::vector<MovAction_t> & action = problem.getActions();
        std::vector<MovAction_t>::iterator it;
#ifdef HW2_DEBUG
        std::cout << "expand node above:\n";
#endif
        for(it=action.begin(); it<action.end(); it++)
        {
            if(*it == MOV_ACT_NOOP) {
                continue;
            }

            MapNode *child = NULL;
            int res = 0;
            res = problem.movAction(node, *it, &child);
            if(res == OP_OK)
            {
                if(!isInQueue(child) && !isInExplored(child))
                {
                    insertQueue(child);
                    traceNode(child);
                }
                else
                {
                    if(isInQueue(child))
                    {
                        //get old one
                        MapNode *old = findQueueByKey(child->getKey());
                        if(child->getPathCost() < old->getPathCost())
                        {
                            //update;
#ifdef HW2_DEBUG
                            std::cout <<"before update, child cost: " << child->getPathCost();
                            std::cout <<", old cost: " << old->getPathCost();
#endif
                            updateQueue(old, child);
#ifdef HW2_DEBUG
                            std::cout <<", after, old cost: " << old->getPathCost() << std::endl;
#endif
                        }
                    }
                }
            }
        }

#ifdef HW2_DEBUG
        std::cout << "expand node over:\n";
#endif
    }

    return false;
}
#endif
}
