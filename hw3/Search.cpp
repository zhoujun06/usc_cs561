#include "Search.h"

extern std::ofstream fprun;

namespace csci561
{

/*
 * function MAX-VALUE(state,α, β) returns a utility value
 * if TERMINAL-TEST(state) then return UTILITY(state)
 * v ← −∞
 * for each a in ACTIONS(state) do
 *      v ← MAX(v, MIN-VALUE(RESULT(s,a),α, β))
 *      if v ≥ β then return v
 *      α← MAX(α, v)
 * return v
 */
int MinMaxS::maxValue(Problem &p, Board *state, int depth, int  alpha, int  beta)
{
    if (p.isTerm(state)) {
        return p.getUtil(state, p._init_c);
    }

    if (depth == 0) {
        return p.getHeUtil(state, p._init_c);
    }

    int v = MIN_INFT;
    static int max_prun_num = 0;

    std::vector<Action> actions;
    std::vector<Action>::iterator it;
    p.getActions(state, actions);

    for (it=actions.begin(); it<actions.end(); it++)
    {
        Board *next = NULL;
        p.doAct(state, &next, *it);
        v = MAX(v, minValue(p, next, depth-1, alpha, beta));
#ifdef WITH_ABP
        char player = p.getPlayer(state);
        alpha = MAX(alpha, v);

        if (v >= beta && it+1 != actions.end()) {
#if 1
            if (max_prun_num++ < 1) { 
                std::cout << "First pruning in Max is as following, other prunnings please see prun.txt\n";
                std::cout << "Player " << player << "'s turn: alpha = " << alpha;
                std::cout << "; beta = " << beta << "; all moves: ";
                std::vector<Action>::iterator pit;
                for(pit=actions.begin(); pit<actions.end(); pit++) {
                    std::cout << "<" << pit->_x << "," << pit->_y << ">, ";
                }
                std::cout << "pruned moves: ";
                for(pit=it+1; pit<actions.end(); pit++) {
                    std::cout << "<" << pit->_x << "," << pit->_y << ">, ";
                }
                std::cout << std::endl;
            }

            fprun << "Player " << player << "'s turn: alpha = " << alpha;
            fprun << "; beta = " << beta << "; all moves: ";
            std::vector<Action>::iterator pit;
            for(pit=actions.begin(); pit<actions.end(); pit++) {
                fprun << "<" << pit->_x << "," << pit->_y << ">, ";
            }
            fprun << "pruned moves: ";
            for(pit=it+1; pit<actions.end(); pit++) {
                fprun << "<" << pit->_x << "," << pit->_y << ">, ";
            }
            fprun << std::endl;
             
#endif
            return v;
        }
#endif
    }

    return v;
}


/*
 * if TERMINAL-TEST(state) then return UTILITY(state)
 * v ← +∞
 * for each a in ACTIONS(state) do
 *      v ← MIN(v, MAX-VALUE(RESULT(s,a) ,α, β))
 *      if v ≤ α then return v
 *      β← MIN(β, v)
 * return v
 */
int MinMaxS::minValue(Problem &p, Board *state, int depth, int  alpha, int  beta)
{
    if (p.isTerm(state)) {
        return p.getUtil(state, p._init_c);
    }

    if (depth == 0) {
        return p.getHeUtil(state, p._init_c);
    }

    int v = MAX_INFT;
    static int min_prun_num = 0;

    std::vector<Action> actions;
    std::vector<Action>::iterator it;
    p.getActions(state, actions);

    for (it=actions.begin(); it<actions.end(); it++)
    {
        Board *next = NULL;
        p.doAct(state, &next, *it);
        v = MIN(v, maxValue(p, next, depth-1, alpha, beta));
#ifdef WITH_ABP
        char player = p.getPlayer(state);
        beta = MIN(beta, v);

        if (v <= alpha && it+1 != actions.end()) {
#if 1
            if (min_prun_num++ < 1) { 
                std::cout << "First pruning in Min is as following, other prunnings please see prun.txt\n";
                std::cout << "Player " << player << "'s turn: alpha = " << alpha;
                std::cout << "; beta = " << beta << "; all moves: ";
                std::vector<Action>::iterator pit;
                for(pit=actions.begin(); pit<actions.end(); pit++) {
                    std::cout << "<" << pit->_x << "," << pit->_y << ">, ";
                }
                std::cout << "pruned moves: ";
                for(pit=it+1; pit<actions.end(); pit++) {
                    std::cout << "<" << pit->_x << "," << pit->_y << ">, ";
                }
                std::cout << std::endl;
            }

            fprun << "Player " << player << "'s turn: alpha = " << alpha;
            fprun << "; beta = " << beta << "; all moves: ";
            std::vector<Action>::iterator pit;
            for(pit=actions.begin(); pit<actions.end(); pit++) {
                fprun << "<" << pit->_x << "," << pit->_y << ">, ";
            }
            fprun << "pruned moves: ";
            for(pit=it+1; pit<actions.end(); pit++) {
                fprun << "<" << pit->_x << "," << pit->_y << ">, ";
            }
            fprun << std::endl;
#endif

            return v;
        }
#endif

    }

    return v;
}

int MinMaxS::doSearch(Problem &p, std::vector<Action> &result, int & res_value)
{
    int alpha = MIN_INFT;
    int beta = MAX_INFT;
    
    int v = MIN_INFT;
    res_value = MIN_INFT;

    //depth limit definition
    int depth = 10;

    std::vector<Action> actions;
    std::vector<Action>::iterator it;
    p.getActions(p._init_state, actions);

    std::vector<int> res_val;

    //for (it=actions.begin(); it<actions.end(); it++)
    for (size_t i=0; i<actions.size(); i++)
    {
        Board *next = NULL;
        p.doAct(p._init_state, &next, actions[i]);
        v = minValue(p, next, depth, alpha, beta);
        if (v > res_value) {
            res_value = v;
        }
        res_val.push_back(v);
    }

    for (size_t i=0; i<res_val.size(); i++) {
        if (res_val[i] == res_value) {
            result.push_back(actions[i]);
        }
    }

    return 0;
}

}
