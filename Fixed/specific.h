#define PEERS UNIT*GRIDSIZE-(UNIT-1)*2-3

struct sudoku {
    squaretype cur[GRIDSIZE*GRIDSIZE];
    squaretype ori[GRIDSIZE*GRIDSIZE];
    bool value[GRIDSIZE*GRIDSIZE][GRIDSIZE+1];      // 可选值 value"1,2,4,5,6" 0-
    squaretype peer[GRIDSIZE*GRIDSIZE][PEERS];		// 
    squaretype rows[GRIDSIzE*GRIDSIZE][GRIDSIZE-1];
    squaretype cols[GRIDSIZE*GRIDSIZE][GRIDSIZE-1];
    squaretype boxes[GRIDSIZE*GRIDSIZE][GRIDSIZE-1];
    bool isvalid = true;
}

