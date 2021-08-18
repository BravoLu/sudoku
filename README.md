# Q&A

General Queries
Had some general queries from someone by email, and thought they'd be better answered here:
a) 11.1 - is solve easy puzzles but be able to read all puzzles?
Yes - you should read all puzzles and solve using the constraint propagation technique outlined.

b)  Is there a requirement to print the grid? 
Yes. The function sudoku_print() is specified in sudoku.h    I haven't specified exactly how to do this though since there's no easy way to test it - it's more to help you debug your code. The function sudoku_tostring() allows a better way to do some assert() testing.

c) What do we do if it's a hard puzzle that we read in ie one it shouldn't be able to solve?
In sudoku.h is says that for sudoku_consprop() :
"Returns true if a complete solution if found, false otherwise"

d) Do I assume a 9x9 grid or do I have to read and calculate square size from the input? (11.3 allows for bigger grids but should we have a 'incorrect square size' check in place?
For 11.1 use a fixed-size grid. For other exercises it's up to you.

e) is specific.h to replace sudoku.h ?
You write sudoku.c & specific.h in a sub-directory called "Fixed" - this mirrors the ADT examples for List/Queue/Stack etc.  

f) Is there an easier intro to the constraint propagation that you could recommend?
I think the link describes it pretty well & in a quite detailed way. Happy to talk about it though if you're struggling.

g) So does 11.2 mean abandoning the constraint propagation and solving this another way?
When constraint propagation still leads to some unknown squares, you effectively take a guess at it, then see if this leads to an invalid solution - if it does, take a different guess instead. Worry about this AFTER you've finished the 1st part though - it'll seem easier then.