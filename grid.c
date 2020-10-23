// Initializes a 2D array of (struct cell*) of size h*w in the heap, all pointers -> NULL
struct cell*** initGrid(int h, int w) {
    struct cell ***grid = malloc( h * sizeof(struct cell**) );
    for(int y=0;y<w;y++){
        grid[y] = calloc( w, sizeof(struct cell*) );
    }
    return grid;
}

// Deallocates heap memory of grid
void freeGrid(int h, struct cell*** grid) {
	for(int y=0;y<h;y++) {
		free(grid[y]);
	}
	free(grid);
}

// Frees all allocated struct cells and sets the pointer to them to NULL
void clearGrid(int h, int w, struct cell*** grid) {
	for(int y=0;y<h;y++) {
		for(int x=0;x<w;x++) {
			if( grid[y][x] != NULL ) {
				free(grid[y][x]);
				grid[y][x] = NULL;
			}
		}
	}
}

// Generates a random grid
void randomizeGrid(int h, int w, struct cell*** grid) {
	// Seed rand
	srand(time(NULL));
	// Clear existing grid
	clearGrid(grid);
	for(int y=0;y<h;y++) {
		for(int x=0;x<w;x++) {
			// Random num with either be 0 or 1
			if(rand() % 2 == 1) 
				newCell(y, x, grid);		
		}
	}
}
