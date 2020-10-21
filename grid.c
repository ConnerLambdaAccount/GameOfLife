#include<stdlib.h>

struct cell*** initGrid(void) {
	struct cell ***grid = malloc( H * sizeof(struct cell**) );
	for(int y=0;y<H;y++){
		for(int x=0;x<W;x++){
			grid[y] = malloc( W * sizeof(struct cell*) );
			grid[y][x] = NULL;
		}
	}
	return grid;
}

void clearGrid(struct cell*** grid) {
	for(int y=0;y<H;y++) {
		for(int x=0;x<W;x++) {
			if( grid[y][x] != NULL ) {
				free(grid[y][x]);
				grid[y][x] = NULL;
			}
		}
	}
}

void printGrid(struct cell*** grid) {
	printf("\e[1;1H\e[2J"); 
	for (int y=0;y<H;y++) {
		for (int x=0;x<W;x++) {
			if (grid[y][x] != NULL)
				printf("#");
			else
				printf(" ");
		}
		printf("\n");
	}
}
