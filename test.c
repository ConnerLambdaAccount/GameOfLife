#include<stdio.h>

#define H 5
#define W 5

#include "grid2.c"

int main(void) {
	struct cell*** grid = initGrid();
	printGrid(grid);
	freeGrid(grid);
}
