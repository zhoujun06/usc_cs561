#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <cstring>
#include <functional>
#include "hw1_include.h"

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

private:
    std::priority_queue<T, std::vector<T>, PrioCompare > _prio_queue;
};

} //namespace

#endif 
