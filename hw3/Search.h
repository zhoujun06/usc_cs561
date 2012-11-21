#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "hw2_include.h"
#include "Problem.h"

namespace csci561
{

class MinMaxS
{
public:
    MinMaxS() {}
    
    ~MinMaxS() {}

    int doSearch(Problem &p, std::vector<Action> &result, int & res_value);
    int maxValue(Problem &p, Board *state, int depth, int  alpha, int  beta);
    int minValue(Problem &p, Board *state, int depth, int  alpha, int  beta);

    std::vector<Action> _path;
};

} //namespace

#endif
