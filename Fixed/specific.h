#include "../sudoku.h"
#define PEERSIZE UNITS*GRIDSIZE-(UNITS-1)*2-3

struct sudoku {
    squaretype cur[GRIDSIZE*GRIDSIZE];
    bool value[GRIDSIZE*GRIDSIZE][GRIDSIZE];      
    int peers[GRIDSIZE*GRIDSIZE][PEERSIZE];		 
    int rows[GRIDSIZE*GRIDSIZE][GRIDSIZE-1];
    int cols[GRIDSIZE*GRIDSIZE][GRIDSIZE-1];
    int boxes[GRIDSIZE*GRIDSIZE][GRIDSIZE-1];
    bool isvalid;
};

