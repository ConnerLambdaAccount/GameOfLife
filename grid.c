#include<stdlib.h>

#include "cell.c"

struct cell*** initGrid(int h, int w) {
	struct cell ***grid = malloc( h * sizeof(struct cell**) );
	for(int y=0;y<h;y++){
		for(int x=0;x<w;x++){
			grid[y] = malloc( w * sizeof(struct cell*) );
			grid[y][x] = NULL;
		}
	}
	return grid;
}

void printGrid(struct cell*** grid, int h, int w) {
	printf("grid: %p\n", grid);
	for (int y=0;y<h;y++) {
		for (int x=0;x<w;x++) {
			if (grid[y][x] != NULL)
				printf("+");
			else
				printf("-");
		}
		printf("\n");
	}
}
