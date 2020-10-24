struct cell {
	int y;
	int x;
};

// NOTE: Cell functions will not perform OOB checks (besides neighborCount)
void newCell(int y, int x, struct cell ***grid) {
	struct cell newCell = { .y=y, .x=x };
	grid[y][x] = malloc(sizeof(struct cell));
	*grid[y][x] = newCell;
}

void remCell(int y, int x, struct cell*** grid) {
	free(grid[y][x]);
	grid[y][x] = NULL;
}

int neighborCount(int y, int x, int h, int w, struct cell*** grid) {
	int neighbors = 0;
	/*
		Function searches all 8 neighbors of [y][x] for populated cells  
		[y-1][x-1]  [y-1][x]  [y-1][x+1]
		[y][x-1]    [y][x]    [y][x+1]
	   	[y+1][x-1]  [y-1][x]  [y-1][x+1]
	*/
	for(int yoffset=-1;yoffset<=1;yoffset++) {
		for(int xoffset=-1;xoffset<=1;xoffset++) {
			// Don't count [y][x] as a neighbor
			if ( !(yoffset == 0 && xoffset == 0) ) {
				// Ensure in bounds of grid
				if( (y+yoffset >= 0 && y+yoffset < h) && (x+xoffset >= 0 && x+xoffset < w) ) {
					// Ensure neighbor is populated
					if( grid[y+yoffset][x+xoffset] != NULL )
						neighbors++;
				}
			}
		}
	}
	return neighbors;
}
