#include "sudoku.h"
#include "specific.h"

#define GRIDSTR 500

/* See examples from :
https://github.com/dimitri/sudoku/
*/

int main(void)
{

   char str[GRIDSTR];
   bool b1[GRIDSIZE] = {true,true,false,true,false,true,true,true,true};
   bool *b2;
   sudoku* s = NULL;

   printf("Basic Sudoku Tests ... Start\n");

   
   sudoku_tostring(s, str); assert(strcmp(str, "") == 0);
   assert(!sudoku_isknown(NULL, 0, 0));
   assert(!sudoku_isvalid(s));

   s = sudoku_init();
   assert(s != NULL);
   sudoku_tostring(s, str); assert(strcmp(str, ".................................................................................")==0);
   assert(sudoku_isknown(s, 0, 0) == false);
   assert(sudoku_isvalid(s));

   assert(sudoku_fromfile(s, "../../Data/Sudoku/9x9-med-32.sud"));
   sudoku_tostring(s, str);
   assert(strcmp(str, "..3.2.6..9..3.5..1..18.64....81.29..7.......8..67.82....26.95..8..2.3..9..5.1.3..")==0);
   assert(sudoku_isknown(s, 2, 0) == true);
   assert(sudoku_isknown(s, 4, 8) == true);
   assert(sudoku_isknown(s, 1, 0) == false);
   assert(sudoku_isknown(s, 0, 8) == false);
   assert(sudoku_isvalid(s));
   assert(sudoku_setsquare(s, 8, 7, 1));
   assert(!sudoku_isvalid(s));
   assert(sudoku_setsquare(s, 8, 7, 0));
   assert(sudoku_setsquare(s, 8, 7, 2));
   assert(!sudoku_isvalid(s));
   assert(sudoku_setsquare(s, 8, 7, 0));
   assert(sudoku_setsquare(s, 7, 0, 1));
   assert(!sudoku_isvalid(s));
   assert(sudoku_setsquare(s, 7, 0, 0));
   assert(sudoku_setsquare(s, 1, 1, 3));
   assert(!sudoku_isvalid(s));
   assert(sudoku_setsquare(s, 1, 1, 0));

   assert(sudoku_isvalid(s));
   assert(sudoku_free(s));

   s = sudoku_init();
   assert(sudoku_fromfile(s, "../../Data/Sudoku/81-hard-17.sud"));
   assert(sudoku_isvalid(s));
   assert(sudoku_free(s));

   s = sudoku_init();
   assert(sudoku_fromfile(s, "../../Data/Sudoku/bars-hard-17.sud"));
   assert(sudoku_isvalid(s));
   assert(sudoku_free(s));

   s = sudoku_init();
   assert(sudoku_fromfile(s, "../../Data/Sudoku/9x9-easy-28.sud"));
   assert(sudoku_isvalid(s));
   b2 = sudoku_taken(s, 8, 1);
   assert(memcmp(b1, b2, sizeof(b1))==0);
   assert(sudoku_consprop(s));
   assert(sudoku_free(s));
   free(b2);

   s = sudoku_init();
   assert(sudoku_fromfile(s, "../../Data/Sudoku/9x9-med-32.sud"));
   assert(sudoku_consprop(s));
   assert(sudoku_free(s));

   s = sudoku_init();
   assert(sudoku_fromfile(s, "../../Data/Sudoku/81-hard-17.sud"));
   assert(!sudoku_consprop(s));
   assert(sudoku_free(s));

   printf("Basic Sudoku Tests ... Stop\n");

   return 0;

}
