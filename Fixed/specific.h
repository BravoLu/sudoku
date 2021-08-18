#define PEERS UNIT*GRIDSIZE-(UNIT-1)*2-3

struct sudoku {
    squaretype cur[GRIDSIZE*GRIDSIZE];
    squaretype ori[GRIDSIZE*GRIDSIZE];
    bool value[GRIDSIZE*GRIDSIZE][GRIDSIZE+1];
    bool peer[GRIDSIZE*GRIDSIZE][PEERS];
    bool units[GRIDSIzE*GRIDSIZE][UNITS];
}

