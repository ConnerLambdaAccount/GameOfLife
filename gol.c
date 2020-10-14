#include<stdio.h>
#include<unistd.h>

#define H 21
#define W 70

#include "grid.c"

int main(void) {
	struct cell*** grid = initGrid(H, W);
	struct cell *cell = newCell(5, 10, grid);
	for (int t=0;;t++) {
		printGrid(grid, H, W);
		printf("%i Generations\n", t);
		sleep(1);
	}
}
