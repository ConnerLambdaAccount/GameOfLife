#include<stdio.h>
#include<unistd.h>

#include "grid.c"

#define W 70
#define H 21

int main(void) {
	struct cell*** grid = initGrid(H, W);
	struct cell cell1 = {.x=5, .y=10, .neighbors=NULL};
	struct cell cell2 = {.x=6, .y=10, .neighbors=NULL};
	for (int t=0;;t++) {
		printGrid(grid, H, W);
		printf("%i Generations\n", t);
		sleep(1);
	}
}
