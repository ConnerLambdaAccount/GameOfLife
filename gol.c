#include<stdio.h>
#include<unistd.h>

#define H 25
#define W 25

#include "gol.h"

int main(void) {
	// Create grid
	struct cell*** grid = initGrid(H, W);

	// Create cells
	struct cell* head = newCell(NULL, 0, 4, grid);
	head = newCell(head, 0, 0, grid);
	head = newCell(head, 0, 1, grid);
	head = newCell(head, 1, 10, grid);
	head = newCell(head, 1, 5, grid);

	// Print game
	printGrid(grid, H, W);
	printAllCells(head, grid);
	
	printf("head: %i\n", neighborCount(head, grid));

}
