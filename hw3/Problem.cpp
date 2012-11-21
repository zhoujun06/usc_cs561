#include "Problem.h"

namespace csci561
{

    Board::Board(int size, char ** data)
    {
        _size = size;
        _data = data;
    }

    Board::~Board()
    {}

    int Board::countChar(char color)
    {
        int cnt = 0;
        for (int i=0; i<_size; i++) {
            for (int j=0; j<_size; j++) {
                if (_data[i][j] == color) {
                    cnt++;
                }
            }
        }

        return cnt;
    }

    int Board::getRedCnt()
    {
        char color = 'r';
        return countChar(color);
    }

    int Board::getGoldCnt()
    {
        char color = 'g';
        return countChar(color);
    }

    int Board::getContinueCnt(int x, int y, bool ** &visited)
    {
        int cnt = 0;
        char color = _data[x][y];

        std::queue<Action> qu;
        qu.push(Action(x, y, color));
        visited[x][y] = true;

        while (!qu.empty()) {
            Action node = qu.front();
            qu.pop();
            cnt++;
            int x = node._x;
            int y = node._y;
            //right, down, left, up
            if (x+1 <= _size-1 && _data[x+1][y] == color && !visited[x+1][y]) {
                qu.push(Action(x+1, y, color));
                visited[x+1][y] = true;
            } 
            if (y+1 <= _size-1 && _data[x][y+1] == color && !visited[x][y+1]) {
                qu.push(Action(x, y+1, color));
                visited[x][y+1] = true;
            } 
            if (x-1 >= 0 && _data[x-1][y] == color && !visited[x-1][y]) {
                qu.push(Action(x-1, y, color));
                visited[x-1][y] = true;
            } 
            if (y-1 >= 0 && _data[x][y-1] == color && !visited[x][y-1]) {
                qu.push(Action(x, y-1, color));
                visited[x][y-1] = true;
            } 
        }

        return cnt;
    }


    int Board::getHeuVal2(Action &act)
    {
        int cnt = 0;
        char color = act._color;
        int x = act._x;
        int y = act._y;
        if (x+1 <= _size-1 && _data[x+1][y] == color) {
            cnt++;
        } 
        if (y+1 <= _size-1 && _data[x][y+1] == color) {
            cnt++;
        } 
        if (x-1 >= 0 && _data[x-1][y] == color) {
            cnt++;
        } 
        if (y-1 >= 0 && _data[x][y-1] == color) {
            cnt++;
        } 

        return cnt;
    }

    int Board::getHeuVal(Action &act, bool ** &visited)
    {
        int cnt = 0;
        char color = act._color;
        int x = act._x;
        int y = act._y;

        std::queue<Action> qu;
        qu.push(Action(x, y, color));
        visited[x][y] = true;

        while (!qu.empty()) {
            Action node = qu.front();
            qu.pop();
            cnt++;
            int x = node._x;
            int y = node._y;
            //right, down, left, up
            if (x+1 <= _size-1 && !visited[x+1][y] && (_data[x+1][y] == color || _data[x+1][y] == '.')) {
                qu.push(Action(x+1, y, color));
                visited[x+1][y] = true;
            } 
            if (y+1 <= _size-1 && !visited[x][y+1] && (_data[x][y+1] == color || _data[x][y+1] == '.')) {
                qu.push(Action(x, y+1, color));
                visited[x][y+1] = true;
            } 
            if (x-1 >= 0 && !visited[x-1][y] && (_data[x-1][y] == color || _data[x-1][y] == '.')) {
                qu.push(Action(x-1, y, color));
                visited[x-1][y] = true;
            } 
            if (y-1 >= 0 && !visited[x][y+1] && (_data[x][y-1] == color || _data[x][y-1] == '.')) {
                qu.push(Action(x, y-1, color));
                visited[x][y-1] = true;
            } 
        }

        return cnt;
    }


    bool ** Board::getArray()
    {
        bool **visited = new bool *[_size];
        visited [0] = new bool[_size * _size];
        for (int i=1; i<_size; i++) {
            visited[i] = visited[i-1] + _size;
        }
        memset(visited[0], false, _size*_size);

        return visited;
    }

    int Board::getScore(char color)
    {
        int cnt = 0;

        bool **visited = new bool *[_size];
        visited [0] = new bool[_size * _size];
        for (int i=1; i<_size; i++) {
            visited[i] = visited[i-1] + _size;
        }
        memset(visited[0], false, _size*_size);


        for (int i=0; i<_size; i++) {
            for (int j=0; j<_size; j++) {
                if (_data[i][j] == color && !visited[i][j]) {
                    int cnt_new = getContinueCnt(i, j, visited);
                    cnt = MAX(cnt, cnt_new);
                }
            }
        }

        delete [] visited[0];
        delete [] visited;

        return cnt;
    }

    int Board::getRedScore()
    {
        return getScore('r');
    }

    int Board::getGoldScore()
    {
        return getScore('g');
    }

    int Board::getHeu(Action act)
    {
#ifdef NO_HEU
        return MIN_INFT;
#else
        int cnt = 0;
        /*
        bool ** visited = getArray();
        cnt = getHeuVal(act, visited);
        delete [] visited[0];
        delete [] visited;
        */
        cnt = getHeuVal2(act);
        return cnt;
#endif
    }

    Problem::Problem(Board *state)
    {
        _init_state = state;
        _init_c = getPlayer(state);
        if (_init_c == 'r') {
            _counter_c = 'g';
        } else {
            _counter_c = 'r';
        }
    }

    Problem::~Problem()
    {
    }

    bool Problem::isTerm(Board *state)
    {
        if (state->getRedCnt() + state->getGoldCnt() == 
                state->getSizeSq())
        {
            return true;
        }

        return false;
    }

    int Problem::getUtil(Board *state, char color)
    {
        int red = state->getRedScore();
        int gold = state->getGoldScore();

        if (color == 'r') {
            return red - gold;
        } else if (color == 'g'){
            return gold - red;
        }

        return MIN_INFT;
    }


    int Problem::getHeUtil(Board *state, char color)
    {
        int red = state->getRedScore();
        int gold = state->getGoldScore();

        if (color == 'r') {
            return red - gold;
        } else if (color == 'g'){
            return gold - red;
        }

        return MIN_INFT;
    }


    int Problem::doAct(Board *cur, Board **next, Action &act)
    {
        char **array = new char *[cur->getSize()];
        array[0] = new char[cur->getSizeSq()];
        for (int i=1; i<cur->getSize(); i++) {
            array[i] = array[i-1] + cur->getSize();
        }

        memcpy(array[0], (cur->_data)[0], cur->getSizeSq());
        array[act._x][act._y] = act._color;

        *next = new Board(cur->getSize(), array);

        return 0;
    }


    int Problem::getActions(Board *state, std::vector<Action> &act)
    {
        char color = getPlayer(state);
        int size = state->getSize();

        int heu = MIN_INFT;
        int res = MIN_INFT;
        std::vector<Action>::iterator it;

        //std::vector<Action> tmp;
        for (int i=0; i<size; i++) {
            for (int j=0; j<size; j++) {
                if ((state->_data)[i][j] == '.') {
                    Action action(i, j, color);
                    res = state->getHeu(action);
                    if (res > heu) {
                        it = act.begin();
                        act.insert(it, action);
                        heu = res;
                    } else {
                        act.push_back(action);
                    }
                }
            }
        }

        return 0;
    }

    char Problem::getPlayer(Board *state)
    {
        if (state->getRedCnt() == state->getGoldCnt()) {
            return 'r';
        } else if (state->getRedCnt() > state->getGoldCnt()) {
            return 'g';
        }

        return 'N';
    }

} //namespace
