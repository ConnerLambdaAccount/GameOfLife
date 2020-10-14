struct cell {
	int x;
	int y;
	struct cell* neighbors[8];
};

// Adds cell to grid
// Returns 0 on success -1 on failure
int newCell(int x, int y, struct cell ***grid) {
	printf("new cell being created @ grid[%i][%i]\n", y, x);
	struct cell* neighbors[8];
	for (int i=0;i<8;i++) {
		
	}
	struct cell newCell = {.x=x, .y=y, .neighbors=neighbors};
	return 0;	
}

