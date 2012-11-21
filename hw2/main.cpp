#include "hw2_include.h"
#include <fstream>
#include "MapNode.h"
#include "Queue.h"
#include "Problem.h"
#include "Search.h"

using namespace csci561;

const int MAX_SIZE = 9;

const char *EUC_SEARCH = "Euclidean_search";
const char *MAN_SEARCH = "Manhattan_search";
const char *CHE_SEARCH = "Chessboard_search";
const char *GMAN_SEARCH = "Greedy_manhattan_search";

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

std::string part1;
std::string part2;

void outputPart2(std::vector<MapNode *> &path)
{
    if (path.size() == 0) {
        part2 += "-1";
        return;
    }

    std::vector<MapNode *>::reverse_iterator rit;
    char buf[1024] = {'\0'};
    rit = path.rbegin()+1;
    for(; rit < path.rend(); rit++)
    {
        snprintf(buf, sizeof(buf), "(%d, %d) ", 
                (*rit)->getNodeA().getX(), 
                (*rit)->getNodeA().getY());
        part2 += buf;
    }

}


void outputRes(bool res, Search *se, Problem &p, std::vector<MapNode *> &path)
{
#ifdef HW2_DEBUG
    if(res == true) 
    {
        std::cout << se->getName() << " ok.\n";
    } else {
        std::cout << se->getName() << " failed.\n";
    }
#endif

    if (false == res) {
        part1 += "-\t\t"; 
        return;
    }
    char buf[1024] = {'\0'};
    if (res) {
        snprintf(buf, sizeof(buf), "%d\t\t", se->getExploredSize());
        part1 += buf;

#ifdef HW2_DEBUG
        std::cout << "explored.size: " << se->getExploredSize() << std::endl;
        std::cout << "path is:\n";
        std::vector<MapNode *>::reverse_iterator rit;
        for(rit = path.rbegin(); rit < path.rend(); rit++)
        {
            se->traceNode(*rit);
        }
        std::cout << "path over.\n";
        std::cout << std::endl;
#endif
    }
}

int main(void)
{
    bool res = false;
    Problem pb;
    std::vector<Node> obs;
    PrioSearch eucsearch(EUC_SEARCH, DIST_EUC);
    std::vector<MapNode *> eucpath;
    PrioSearch mansearch(MAN_SEARCH, DIST_MAN);
    std::vector<MapNode *> manpath;
    PrioSearch chesearch(CHE_SEARCH, DIST_CHE);
    std::vector<MapNode *> chepath;

    std::vector<MapNode *> gmanpath;

    int size;
    int x1, y1;
    int x2, y2;
    int ctop = 2;
    int cright = 2;
    int cdown = 2;
    int cleft = 2;
    int obx, oby;

    if (fin.fail()) {
        std::cout << "failed to open input.txt\n";
        return -1;
    }

    if (fout.fail()) {
        std::cout << "failed to open output.txt\n";
        return -1;
    }

    part1 += "\t\tNodes Expanded\n";
    part1 += "\tEuclidean\tManhattan\tChessboard\n";
    part2 += "Optimal Path Solution:\n";

    int i=0;
    char line[1024] = {'\0'};
    while (fin.getline(line, sizeof(line))) 
    { 
        if (strlen(line) == 0) {
            continue;
        }
        char buf[1024] = {'\0'};
        snprintf(buf, sizeof(buf), "Input%d:\t", ++i);
        part1 += buf;
        part2 += buf;

        //std::cout << line << std::endl;
        sscanf(line, "%d", &size);
        if(size < 1 || size > MAX_SIZE)
        {
            std::cout << "size over range, should be 1-9\n";
            return -1;
        }
        // fin >> ctop >> cright>> cdown>> cleft;
        if(ctop <1 || cright <1 || cdown <1 || cleft <1)
        {
            std::cout << "path cost should be positive\n";
            return -1;
        }

        fin.getline(line, sizeof(line));
        //std::cout << line << std::endl;
        sscanf(line, "%d %d", &x1, &y1);
        fin.getline(line, sizeof(line));
        //std::cout << line << std::endl;
        sscanf(line, "%d %d", &x2, &y2);
        if(x1<1 || x1>size || x2<1 || x2>size ||
                y1<1 || y1>size || y2<1 || y2>size )
        {
            std::cout << "obstacles should be in size range.\n";
            return -1;
        }

#ifdef HW2_DEBUG
        std::cout << size << std::endl;
        std::cout << x1 << " " << y1 << std::endl;
        std::cout << x2 << " " << y2 << std::endl;
#endif

        while(fin.good() && fin.getline(line, sizeof(line)))
        {
            //std::cout << line << std::endl;
            if (strlen(line) == 0) {
                break;
            }
            sscanf(line, "%d %d", &obx, &oby);
#ifdef HW2_DEBUG
            std::cout << obx << " " << oby << std::endl;
#endif
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

        pb.clearMember();
        pb.setSize(size);
        pb.setInitState(x1, y1, x2, y2);
        pb.setObstacles(obs);
        pb.setActions(ctop, cright, cdown, cleft);

#if 0
        BFSearch bfsearch;
        std::vector<MapNode *> bfpath;
        UCSearch ucsearch;
        std::vector<MapNode *> ucpath;

        bfpath.clear();
        ucpath.clear();

        std::cout << "bfsearch start.\n";
        res = bfsearch.doSearch(pb, bfpath);
        if(res == true)
        {
            std::cout << "bfsearch ok.\n";
        } else {
            std::cout << "bfsearch failed.\n";
        }
        outputRes(res, &bfsearch, pb, bfpath);

        res = false;
        std::cout << "ucsearch start.\n";
        res = ucsearch.doSearch(pb, ucpath);
        if(res == true) 
        {
            std::cout << "ucsearch ok.\n";
        } else {
            std::cout << "ucsearch failed.\n";
        }
        outputRes(res, &ucsearch, pb, ucpath);
#endif

        res = false;
        res = eucsearch.doSearch(pb, eucpath);
        outputRes(res, &eucsearch, pb, eucpath);

        res = false;
        res = mansearch.doSearch(pb, manpath);
        outputRes(res, &mansearch, pb, manpath);

        res = false;
        res = chesearch.doSearch(pb, chepath);
        outputRes(res, &chesearch, pb, chepath);

#ifdef WITH_GREEDY_MAN
        res = false;
        PrioSearch gmansearch(GMAN_SEARCH, DIST_GREEDY_MAN);
        res = gmansearch.doSearch(pb, gmanpath);
        outputRes(res, &gmansearch, pb, gmanpath);
#endif


        //output part2
        //if all path length are the same, select manhanton
        //otherwise, chose the shortest path

        int eucsize = eucpath.size();
        int mansize = manpath.size();
        int chesize = chepath.size();

        if (mansize <= eucsize && mansize <= chesize) {
            outputPart2(manpath);
        } else if (eucsize <= mansize && eucsize <= chesize) {
            outputPart2(eucpath);
        } else if (chesize <= eucsize && chesize <= mansize) {
            outputPart2(chepath);
        }

        //clear all the info this run
        obs.clear();
        eucpath.clear();
        manpath.clear();
        chepath.clear();
        gmanpath.clear();

        part1 += "\n";
        part2 += "\n";
    } // while (fin.good())

    fout << part1 << std::endl << part2;
#ifdef HW2_DEBUG
    std::cout << part1 << std::endl << part2;
#endif
    fin.close();
    fout.close();

    return 0;
}
