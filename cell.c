struct cell {
	int x;
	int y;
	struct cell** neighbors;
};

// Adds cell to grid
// Will segfault if OOB coordinates provided
struct cell* newCell(int y, int x, struct cell ***grid) {
	printf("new cell being created @ grid[%i][%i]\n", y, x);
	struct cell* neighbors[8];
	
	int i = 0; // neighbors[] index
	for (int y_offset=-1;y_offset<=1;y_offset++) {
		for (int x_offset=-1;x_offset<=1;x_offset++) {

			// Check neighbor is in bounds of grid
			if( (y+y_offset >= 0 && y+y_offset <= H-1) && (x+x_offset >= 0 && x+x_offset <= W-1) ) {
				neighbors[i] = grid[y+y_offset][x+x_offset];
				printf("neighbors[%i] = grid[%i][%i] (%p)\n", i, y+y_offset, x+x_offset, grid[y+y_offset][x+x_offset]);
			}

			i++;

			// Skip adding newCell as a neighbor			
			if (i == 4) {
				i++;
				x_offset++;
			}
		}
	}

	struct cell *newCell = malloc(sizeof(struct cell));
	struct cell addCell = {.x=x, .y=y, .neighbors=neighbors};
	*newCell = addCell;
	grid[y][x] = newCell;
	return newCell;	
}

void printCell(struct cell* inputCell) {
	// Cell addr
	printf("addr: %p\n", inputCell);
	printf("y: %i\n", inputCell->y);
	printf("x: %i\n", inputCell->x);
	printf("neighbors addr: %p\n", inputCell->neighbors);
	for (int i=0;i<8;i++) {
		printf("\t[%i] = %p\n", i, inputCell->neighbors[i]);
	}
}
