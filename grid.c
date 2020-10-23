struct cell*** initGrid(void) {
    struct cell ***grid = malloc( H * sizeof(struct cell**) );
    for(int y=0;y<H;y++){
        grid[y] = calloc( W, sizeof(struct cell*) );
    }
    return grid;
}

void freeGrid(struct cell*** grid) {
	for(int y=0;y<H;y++) {
		free(grid[y]);
	}
	free(grid);
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

void randomizeGrid(struct cell*** grid) {
	// Seed rand
	srand(time(NULL));

	clearGrid(grid);
	for(int y=0;y<H;y++) {
		for(int x=0;x<W;x++) {
			if(rand() % 2 == 1) 
				newCell(y, x, grid);		
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
				printf("-");
		}
		printf("\n");
	}
}
