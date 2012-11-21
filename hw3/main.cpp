#include "hw2_include.h"
#include "Problem.h"
#include "Search.h"
#include <time.h>

using namespace csci561;

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");
std::ofstream fprun("prun.txt");

Board * doInput()
{
    int size = 0;

    char line[1024] = {'\0'};
    while (strlen(line) == 0 && !fin.eof()) {
        fin.getline(line, sizeof(line));
    }
    if(fin.eof()) {
        exit(0);
    }

    sscanf(line, "%d", &size);

    char ** board = new char *[size];
    board[0] = new char[size * size];
    for (int i=1; i<size; i++) {
        board[i] = board[i-1] + size;
    }
    memset(board[0], '.', size*size);

    int num = 0;
    while (num < size && !fin.eof() && fin.getline(line, sizeof(line))) {
        if (strlen(line) == 0) {
            continue;
        }
        strncpy(board[num], line, size);
        num++;
    }
    if (num < size) {
        std::cout << "bad input file." << std::endl;
        exit(1);
    }
    /*  
    for (int i=0; i<size; i++)
    {
        fin.getline(line, sizeof(line));
        strncpy(board[i], line, size);
    }*/

#ifdef DEBUG
    for (int i=0; i<size; i++)
    {
        for (int j=0; j<size; j++) {
            std::cout << board[i][j];
        }
        std::cout << std::endl;
    }
#endif

    Board *init_state = new Board(size, board);

    return init_state;
}


int main(void)
{
    Board *init_state = NULL;

    while (!fin.eof()) {
        init_state = doInput();
        if (init_state == NULL) {
            return -1;
        }

        Problem p(init_state);

        MinMaxS search;

        int res_value = MIN_INFT;
        std::vector<Action> result;

        
        time_t start = time(NULL);
        search.doSearch(p, result, res_value);
        time_t end = time(NULL);

        std::cout << "seconds used " << end-start << std::endl;

        for(size_t i=0; i<result.size(); i++) {
            fout << "(" << result[i]._x << "," << result[i]._y << ") ";
            std::cout << "(" << result[i]._x << "," << result[i]._y << ") ";
        }
        fout << res_value << std::endl;
        std::cout << res_value << std::endl;

        result.clear();
    }

    return 0;
}
