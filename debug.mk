CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -pedantic -std=c90 -Werror
DEBUG= -g3
SANITIZE= -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS=

all: debug

debug: sudoku.h Fixed/specific.h Fixed/fixed.c debugsudoku.c ADTs/General/general.h ADTs/General/general.c
	$(CC) debugsudoku.c Fixed/fixed.c ADTs/General/general.c -o debug -I./Fixed $(PRODUCTION) $(LDLIBS)


clean:
	rm -f testfixed testfixed_s testfixed_v 

run: all
	@./testfixed_s
