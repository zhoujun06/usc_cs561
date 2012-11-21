#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <cstring>
#include <functional>
#include "hw2_include.h"

namespace csci561
{

enum QueueType_t
{
    FIFO_QUEUE = 1,
    LIFO_QUEUE,
    PRIO_QUEUE,
};

/*
template <class T>
class HashTable
{
    typedef int(*hashFunc_t) (T &item);

    HashTable(hashFunc_t func)
    {
        _hash_func = func;
    }

    void setItem(T &item)
    {
        int key = (*_hash_func)(item);
        _map.insert(key, item);
    }

    void delItem(T &item)
    {
        int key = (*_hash_func)(item);
        _map.erase(key);
    }

    T getItem(int key)
    {
        typename std::map<int, T>::iterator it;
        it = _map.find(key);
        if(it != _map.end())
        {
            return it->second;
        }
    }

    bool isKeyExist(int key)
    {
        if(_map.find(key) != _map.end())
        {
            return true;
        }

        return false;
    }

    bool isExist(T &item)
    {
        int key = (*_hash_func)(item);

        return isKeyExist(key);
    }

private:
    hashFunc_t _hash_func;
    std::map<int, T> _map;
};

*/
template <class T>
class Queue
{
public:

    virtual bool isEmpty()=0;

    virtual T pop()=0;

    virtual void push(T& item)=0;

    virtual size_t size()=0;

    virtual void clear()=0;

};

template <class T>
class FIFOQueue : public Queue<T> {
public:

    bool isEmpty()
    {
        return _fifo_queue.empty();
    }

    T pop()
    {
        T item = _fifo_queue.front();
        _fifo_queue.pop();

        return item;
    }

    void push(T& item)
    {
        _fifo_queue.push(item);
    }

    size_t size()
    {
        return _fifo_queue.size();
    }

    void clear()
    {
        while (!_fifo_queue.empty()) {
            _fifo_queue.pop();
        }
    }

private:
    std::queue<T> _fifo_queue;

};

class PrioCompare
{
public:
    PrioCompare(const bool &reverse = false)
    {
        _reverse = reverse;
    }

    bool operator() (const MapNode *ln, const MapNode *rn) const
    {
        if(_reverse) 
            return ln->getPathCost() < rn->getPathCost();
        else
            return ln->getPathCost() > rn->getPathCost();
    }

private:
    bool _reverse;
};

template <class T>
class PrioQueue : public Queue<T>
{
public:
    bool isEmpty()
    {
        return _prio_queue.empty();
    }

    T pop()
    {
        T item = _prio_queue.top();
        _prio_queue.pop();
        return item;
    }

    void push(T& item)
    {
        _prio_queue.push(item);
    }

    size_t size()
    {
        return _prio_queue.size();
    }

    void clear()
    {
        while (!_prio_queue.empty()) {
            _prio_queue.pop();
        }
    }

private:
    std::priority_queue<T, std::vector<T>, PrioCompare > _prio_queue;
};

class EucCompare
{
public:
    bool operator() (const MapNode *ln, const MapNode *rn) const
    {
        if (ln->getEucDist() == rn->getEucDist()) {
            //when this, we choose the one that has already take more steps
#ifdef BIG_GX
            return ln->getPathCost() < rn->getPathCost();
#else
            return ln->getPathCost() > rn->getPathCost();
#endif
        } else {
            return ln->getEucDist() > rn->getEucDist();
        }
    }
};

class ManCompare
{
public:
    bool operator() (const MapNode *ln, const MapNode *rn) const
    {
        if (ln->getManDist() == rn->getManDist()) {
            //when this, we choose the one that has already take more steps
#ifdef BIG_GX
            return ln->getPathCost() < rn->getPathCost();
#else
            return ln->getPathCost() > rn->getPathCost();
#endif
        } else {
            return ln->getManDist() > rn->getManDist();
        }
    }
};

class GreedyManCompare
{
public:
    bool operator() (const MapNode *ln, const MapNode *rn) const
    {
        if (ln->getGreedyManDist() == rn->getGreedyManDist()) {
            //when this, we choose the one that has already take more steps
#ifdef BIG_GX
            return ln->getPathCost() < rn->getPathCost();
#else
            return ln->getPathCost() > rn->getPathCost();
#endif
        } else {
            return ln->getGreedyManDist() > rn->getGreedyManDist();
        }
    }
};

class CheCompare
{
public:
    bool operator() (const MapNode *ln, const MapNode *rn) const
    {
       if (ln->getCheDist() == rn->getCheDist()) {
            //when this, we choose the one that has already take more steps
#ifdef BIG_GX
            return ln->getPathCost() < rn->getPathCost();
#else
            return ln->getPathCost() > rn->getPathCost();
#endif
        } else {
            return ln->getCheDist() > rn->getCheDist();
        }
    }
};

enum DistType_t
{
    DIST_EUC = 1,
    DIST_MAN,
    DIST_CHE,
    DIST_GREEDY_MAN,
};


template <class T>
class EucQueue : public Queue<T>
{
public:
    bool isEmpty()
    {
        return _queue.empty();
    }

    T pop()
    {
        T item = _queue.top();
        _queue.pop();
        return item;
    }

    void push(T& item)
    {
        _queue.push(item);
    }

    size_t size()
    {
        return _queue.size();
    }

    void clear()
    {
        while (!_queue.empty()) {
            _queue.pop();
        }
    }

private:
    std::priority_queue<T, std::vector<T>, EucCompare > _queue;
};

template <class T>
class ManQueue : public Queue<T>
{
public:
    bool isEmpty()
    {
        return _queue.empty();
    }

    T pop()
    {
        T item = _queue.top();
        _queue.pop();
        return item;
    }

    void push(T& item)
    {
        _queue.push(item);
    }

    size_t size()
    {
        return _queue.size();
    }

    void clear()
    {
        while (!_queue.empty()) {
            _queue.pop();
        }
    }

private:
    std::priority_queue<T, std::vector<T>, ManCompare > _queue;
};

template <class T>
class GreedyManQueue : public Queue<T>
{
public:
    bool isEmpty()
    {
        return _queue.empty();
    }

    T pop()
    {
        T item = _queue.top();
        _queue.pop();
        return item;
    }

    void push(T& item)
    {
        _queue.push(item);
    }

    size_t size()
    {
        return _queue.size();
    }

    void clear()
    {
        while (!_queue.empty()) {
            _queue.pop();
        }
    }

private:
    std::priority_queue<T, std::vector<T>, GreedyManCompare > _queue;
};

template <class T>
class CheQueue : public Queue<T>
{
public:
    bool isEmpty()
    {
        return _queue.empty();
    }

    T pop()
    {
        T item = _queue.top();
        _queue.pop();
        return item;
    }

    void push(T& item)
    {
        _queue.push(item);
    }

    size_t size()
    {
        return _queue.size();
    }

    void clear()
    {
        while (!_queue.empty()) {
            _queue.pop();
        }
    }

private:
    std::priority_queue<T, std::vector<T>, CheCompare > _queue;
};


} //namespace

#endif 
