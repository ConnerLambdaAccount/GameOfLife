#include<stdlib.h>
#include "cell.c"

// Initialize 2d array of pointers to -> cell structures
struct cell*** initGrid(int h, int w) {

	// Allocate memory for y-axis pointers, which will point to an array of pointers of size x
	// ex: grid[y] points to -> [0][1][2][3]...[h-1]
	struct cell ***grid = malloc( h * sizeof(struct cell**) );

	// loop through [y][x] in 2d array
	for(int y=0;y<h;y++){
		for(int x=0;x<w;x++){
			// every grid[y] will be allocated an array of pointers to -> cell structures
			grid[y] = malloc( w * sizeof(struct cell*) );
			// every cell structure pointer is set to NULL, cell addition is handled by "cell.c"
			grid[y][x] = NULL;
		}
	}

	return grid;
}

// Print grid 
void printGrid(struct cell*** grid, int h, int w) {
	// Clear screen with regex
	printf("\e[1;1H\e[2J"); 

	// Loop through every pointer in grid
	for (int y=0;y<h;y++) {
		for (int x=0;x<w;x++) {

			// + indicates cell
			if (grid[y][x] != NULL)
				printf("+");
		
			// - indicates empty space
			else
				printf("-");
		}
		printf("\n");
	}

}
