// Cell structure definition
struct cell {
	int y;
	int x;
	struct cell* next;
};

// Helper function to return index of node as if it were in a 1D array
int hashCell(struct cell* c) {
	return c->x + (c->y * H);
}

// 1. Adds cell to grid
// 2. Links that cell in a linked list to its .prev and .next neighbors
// ^ This is done for a less intensive iteration through the 2d array, by only iterating through non-null cells in the array
// NOTE: Will segfault if OOB coordinates provided
// RET: head of list
struct cell* newCell(struct cell* head, int y, int x, struct cell ***grid) {

	// Init newCell with no pointers
	struct cell newCell = { .y=y, .x=x, .next=NULL };

	// Allocate space for cell structure 
	grid[y][x] = malloc(sizeof(struct cell));
	
	if(!head) {
		// Head is NULL, newCell is the new head
		*grid[y][x] = newCell;
		return grid[y][x];
	}

	// if head exists, we must add this newCell to the linked list, otherwise it is presumed newCell IS the head
	// Must add newCell to it's spot in the list
	// To do this, it must be added either:
	// 1. between two nodes
	// 2. before the head
	// 3. at the end of the list 
	// 4. newCell is the head (handled above)

	// 1. before the head:
	// Determine which cell comes first in the grid
	int headHash = hashCell(head);
	int newCellHash = hashCell(&newCell);
	
	if(headHash > newCellHash) {
	
		// newCell is being added BEFORE the current head
		newCell.next = head;
		*grid[y][x] = newCell;

		// Return new head
		return grid[y][x];

	} else {
		// newCell is being added AFTER the current head
		// Must find what cells it will be between: [left] [] [right]
		struct cell* left = head;
		struct cell* right = head->next;

		while(right != NULL) {
			// 2. between two nodes
			int leftHash = hashCell(left);
			int rightHash = hashCell(right);

			// newCellHash indicates it should be BETWEEN left and right nodes
			if (leftHash < newCellHash && rightHash > newCellHash) {
				left->next = grid[y][x];
				newCell.next = right;
				*grid[y][x] = newCell;
				return head;
			}
		
			// Cycle left and right
			left = right;
			right = left->next;
		}

		// 3. at the end of the list
		// Reached end of list, append newCell to end
		left->next = grid[y][x];
		*grid[y][x] = newCell;
		return head;
	}
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
