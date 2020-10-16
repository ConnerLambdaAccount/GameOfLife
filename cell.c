// Cell structure definition
struct cell {
	int y;
	int x;
	struct cell* next;
};

// 1. Adds cell to grid
// 2. Links that cell in a linked list to its .prev and .next neighbors
// ^ This is done for a less intensive iteration through the 2d array, by only iterating through non-null cells in the array
// NOTE: Will segfault if OOB coordinates provided
struct cell* newCell(struct cell* firstCell, int y, int x, struct cell ***grid) {

	// Init newCell with no pointers
	struct cell newCell = { .y=y, .x=x, .next=NULL };

	// Allocate space for cell structure 
	grid[y][x] = malloc(sizeof(struct cell));
	*grid[y][x] = newCell;

	// TODO: Link grid[y][x] to .next neighbor

	return grid[y][x];	
}

// Display cell information
void printCell(struct cell* c) {
	printf("addr: %p\n", c);
	if (c) {
		printf("y: %i\n", c->y);
		printf("x: %i\n", c->x);
		printf("next: %p\n", c->next);
	}
}
