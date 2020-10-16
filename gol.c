#include<stdio.h>
#include<unistd.h>

#define H 25
#define W 25

#include "grid.c"

int main(void) {
	// Create grid
	struct cell*** grid = initGrid(H, W);

	// Create cells
	struct cell* head = newCell(NULL, 5, 10, grid);
	printCell(head);
	head = newCell(head, 5, 11, grid);
	printCell(head);

	// Print game
	printGrid(grid, H, W);
}
