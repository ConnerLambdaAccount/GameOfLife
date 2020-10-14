struct cell {
	int x;
	int y;
	struct cell** neighbors;
};

// Adds cell to grid
// Will segfault if OOB coordinates provided
struct cell* newCell(int x, int y, struct cell ***grid) {
	printf("new cell being created @ grid[%i][%i]\n", y, x);
	struct cell* neighbors[8];
	for (int i=0;i<8;i++) {
		neighbors[i] = NULL;
	}
	/*
	int i = 0; // neighbors[] index
	for (int y_offset=-1;y_offset<=1;y_offset++) {
		for (int x_offset=-1;x_offset<=1;x_offset++) {
			// Check neighbor is in bounds of grid
			if( (y+y_offset >= 0 && y+y_offset <= H-1) && (x+x_offset >= 0 && x+x_offset <= W-1) )
				neighbors[i] = grid[y+y_offset][x+x_offset];
			i++;
			
			if(i == 4)	// skip self as neighbor
				i++;
		}
	}*/
		// [0] == [y-1][x-1]
		// [1] == [y-1][x]
		// [2] == [y-1][x+1]
	
		// [3] == [y][x-1]
		// [cell] == [y][x]
		// [4] == [y][x+1]
		
		// [5] == [y+1][x-1]
		// [6] == [y+1][x]
		// [7] == [y+1][x+1]
	struct cell *newCell = malloc(sizeof(struct cell));
	struct cell myCell = {.x=x, .y=y, .neighbors=neighbors};
	*newCell = myCell;
	grid[y][x] = newCell;
	return newCell;	
}

