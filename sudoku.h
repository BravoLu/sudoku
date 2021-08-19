#pragma once

#include "ADTs/General/general.h"
#include "ADTs/General/bool.h"

typedef struct sudoku sudoku;

enum unittype {row, col, box};
typedef enum unittype unittype;
#define UNITS 3

#define BOX 3
#define GRIDSIZE (BOX*BOX)

typedef unsigned char squaretype;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Create an empty sudoku */
sudoku* sudoku_init(void);

/* Sets square (x, y) to the value v
   / squaretype has error? 
   x {0 ... 8}  y {0 ... 8} v:{1 ... 9}
   Returns true if grid is still valid or false if :
   1) Grid is invalid
   2) s==NULL
   3) x,y,v are out-of-range
*/
bool sudoku_setsquare(sudoku* s, int x, int y, squaretype v);

/* Fill squares from file
   Unknown squares can be '0, '?', '.' etc.
*/

bool sudoku_fromfile(sudoku* s, char* fname);

/* Helps with visualisation & testing */
void sudoku_tostring(sudoku* q, char* str);

/* Output s to screen */
void sudoku_print(sudoku* s);

/* Whether a particular square is known (fixed) yet or not
   x {0 ... 8}     y {0 ... 8}
*/
bool sudoku_isknown(sudoku* s, int x, int y);

/* Returns whether the grid is valid. An invalid grid would
have e.g. two of the same number in a row, column or box etc.
*/
bool sudoku_isvalid(sudoku* s);

/* Returns an array of Booleans which state which of the numbers
are already 'taken' in the peers of square (x, y).
If a '1' appears in the same row/column/box then the first element of this array is true etc.
Memory will need to be free()'d later
*/
bool* sudoku_taken(sudoku* s, int x, int y);

/* Solve the puzzle by applying (https://norvig.com/sudoku.html) only
the "Constraint Propagation" techniques :
(1) If a square has only one possible value, then eliminate that value from the square's peers.
(2) If a unit has only one possible place for a value, then put the value there.
Returns true if a complete solution if found, false otherwise.
*/
bool sudoku_consprop(sudoku* s);

/* Clears all space used */
bool sudoku_free(sudoku* q);

void test_peers_units(sudoku* s, int x, int y);

void print_values(sudoku* s, int x, int y);