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
	head = newCell(head, 1, 10, grid);
	head = newCell(head, 1, 5, grid);

	// Print game
	printGrid(grid, H, W);
	printAllCells(head, grid);

	struct cell*** neighbors = getCellNeighbors(head, grid);
	printf("getCellNeighbors(head) returned: %p\n", neighbors);
	for (int i=0;i<8;i++) {
		if( neighbors[i] == NULL ) {
			printf("\tneighbors[%i] = NULL\n", i);
		} else {
			if( *neighbors[i] == NULL )
				printf("\tneighbors[%i] = %p\t(empty)\n", i);
			else
				printf("\tneighbors[%i] = %p\t (grid[%i][%i])\n", i, neighbors[i], *neighbors[i]->y, *neighbors[i]->x);
		}
	}
}
