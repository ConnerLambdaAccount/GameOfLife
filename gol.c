#include<stdio.h>
#include<unistd.h>

#define H 21
#define W 70

#include "grid.c"

int main(void) {
	// Create grid
	struct cell*** grid = initGrid(H, W);

	// Create cells
	struct cell* head = newCell(NULL, 5, 10, grid);

	// Print game
	printGrid(grid, H, W);
}
