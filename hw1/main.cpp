#include "hw1_include.h"
#include <fstream>
#include "MapNode.h"
#include "Queue.h"
#include "Problem.h"
#include "Search.h"



using namespace csci561;

const int MAX_SIZE = 20;

int main(void)
{
#if 1

    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int size;
    int x1, y1;
    int x2, y2;
    int ctop, cright, cdown, cleft;
    int obx, oby;

    fin >> size;
    if(size < 1 || size > MAX_SIZE)
    {
        std::cout << "size over range, should be 1-9\n";
        return -1;
    }
    fin >> ctop >> cright>> cdown>> cleft;
    if(ctop <1 || cright <1 || cdown <1 || cleft <1)
    {
        std::cout << "path cost should be positive\n";
        return -1;
    }
    fin >> x1 >> y1;
    fin >> x2 >> y2;
    if(x1<1 || x1>size || x2<1 || x2>size ||
       y1<1 || y1>size || y2<1 || y2>size )
    {
        std::cout << "obstacles should be in size range.\n";
        return -1;
    }

    std::vector<Node> obs;
    while(fin.good())
    {
        fin >> obx >> oby;
        if((obx == x1 && oby == y1) || (obx == x2 && oby == y2))
        {
            std::cout << "obstacle is same as A or B. ";
            std::cout << "x: " << obx << ", y: " << oby << std::endl;
            return -1;
        } else {
            Node nd = Node(obx, oby);
            obs.push_back(nd);
        }
    }

    Problem pb;
    pb.setSize(size);
    pb.setInitState(x1, y1, x2, y2);
    pb.setObstacles(obs);
    pb.setActions(ctop, cright, cdown, cleft);

    BFSearch bfsearch;
    bool res = false;
    std::vector<MapNode *> bfpath;
    res = bfsearch.doSearch(pb, bfpath);
    if(res == true)
    {
        fout << bfpath.size()-1 << std::endl; 

        std::vector<MapNode *>::reverse_iterator rit;
        for(rit = bfpath.rbegin(); rit < bfpath.rend(); rit++)
        {
#ifdef HW1_DEBUG
            std::cout << "\tA x: " << (*rit)->getNodeA().getX();
            std::cout << "\tA y: " << (*rit)->getNodeA().getY();
            std::cout << "\tB x: " << (*rit)->getNodeB().getX();
            std::cout << "\tB y: " << (*rit)->getNodeB().getY();
            std::cout << std::endl;
#endif

            fout << (*rit)->getNodeA().getX() << " ";
            fout << (*rit)->getNodeA().getY() << std::endl;
        }
    }
    else
    {
        fout << -1 << std::endl;
#ifdef HW1_DEBUG
        std::cout << "BFSearch failed;" << std::endl;
#endif
    }

    fout << std::endl;
    std::cout << std::endl;

    UCSearch ucsearch;
    res = false;
    std::vector<MapNode *> ucpath;
    res = ucsearch.doSearch(pb, ucpath);
    if(res == true)
    {
        int path_cost = ucpath[0]->getPathCost();
        fout << path_cost << std::endl; 

        std::vector<MapNode *>::reverse_iterator rit;
        for(rit = ucpath.rbegin(); rit < ucpath.rend(); rit++)
        {
#ifdef HW1_DEBUG
            std::cout << "\tA x: " << (*rit)->getNodeA().getX();
            std::cout << "\tA y: " << (*rit)->getNodeA().getY();
            std::cout << "\tB x: " << (*rit)->getNodeB().getX();
            std::cout << "\tB y: " << (*rit)->getNodeB().getY();
            std::cout << std::endl;
#endif

            fout << (*rit)->getNodeA().getX() << " ";
            fout << (*rit)->getNodeA().getY() << std::endl;
        }
    }
    else
    {
        fout << -1 << std::endl;
#ifdef HW1_DEBUG
        std::cout << "UCSearch failed;" << std::endl;
#endif
    }


    fin.close();
    fout.close();

#else

    PrioQueue<MapNode *> pq;
    MapNode *n1 = new MapNode(1, 1, 2, 2, NULL, MOV_ACT_TOP, 10);
    MapNode *n2 = new MapNode(1, 1, 2, 2, NULL, MOV_ACT_TOP, 1);
    MapNode *n3 = new MapNode(1, 1, 2, 2, NULL, MOV_ACT_TOP, 20);
    MapNode *n4 = new MapNode(1, 1, 2, 2, NULL, MOV_ACT_TOP, 10);
    pq.push(n1);
    pq.push(n2);
    pq.push(n3);
    pq.push(n4);
    std::cout << pq.pop()->getPathCost() << std::endl;
    std::cout << pq.pop()->getPathCost() << std::endl;
    std::cout << pq.pop()->getPathCost() << std::endl;
    std::cout << pq.pop()->getPathCost() << std::endl;
    /*
    int a=288;
    int b=299;
    int c=29;



    FIFOQueue<int> queue;
    Queue<int> *qbase = &queue;
    queue.push(a);
    queue.push(b);
    std::cout << "size: " << qbase->size() << std::endl;
    std::cout << qbase->pop() << "\t" << queue.pop() << std::endl;

    std::cout << "size: " << qbase->size();


    PrioQueue<int> pq;
    Queue<int> *qb = &pq;
    pq.push(a);
    pq.push(b);
    qb->push(c);
    std::cout << "size: " << qb->size() << std::endl;
    std::cout << qb->pop() << "\t" << pq.pop() << "\t" << qb->pop() << std::endl;

    std::cout << "size: " << pq.size();
    */
#endif
    return 0;
}
