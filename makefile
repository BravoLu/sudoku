CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -pedantic -std=c90 -Werror
DEBUG= -g3
SANITIZE= -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS=

all: testfixed testfixed_s testfixed_v

testfixed: sudoku.h Fixed/specific.h Fixed/fixed.c testsudoku.c ADTs/General/general.h ADTs/General/general.c
	$(CC) testsudoku.c Fixed/fixed.c ADTs/General/general.c -o testfixed -I./Fixed $(PRODUCTION) $(LDLIBS)

testfixed_s: sudoku.h Fixed/specific.h Fixed/fixed.c testsudoku.c ADTs/General/general.h ADTs/General/general.c
	$(CC) testsudoku.c Fixed/fixed.c ADTs/General/general.c -o testfixed_s -I./Fixed $(SANITIZE) $(LDLIBS)

testfixed_v: sudoku.h Fixed/specific.h Fixed/fixed.c testsudoku.c ADTs/General/general.h ADTs/General/general.c
	$(CC) testsudoku.c Fixed/fixed.c ADTs/General/general.c -o testfixed_v -I./Fixed $(VALGRIND) $(LDLIBS)

clean:
	rm -f testfixed testfixed_s testfixed_v 

run: all
	@./testfixed_s
	@valgrind --quiet ./testfixed_v
