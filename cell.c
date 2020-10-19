#include <stdlib.h>
// Cell structure definition
struct cell {
	int y;
	int x;
	struct cell* next;
	struct cell* prev;
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
	struct cell newCell = { .y=y, .x=x, .prev=NULL, .next=NULL };

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
		head->prev = grid[y][x];
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
				right->prev = grid[y][x];

				newCell.next = right;
				newCell.prev = left; // ADDED for .prev support

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
		newCell.prev = left; // ADDED for .prev support
		*grid[y][x] = newCell;
		return head;
	}
}

struct cell* remCell(struct cell* c) {
	// set c->prev->next = c->next
	// deallocate c
	return NULL;
}

// Return amount of cell neighbors
int neighborCount(int y, int x, struct cell*** grid) {

	int neighbors = 0;

	// Loop through all 8 possible neighbors
	for(int yoffset=-1;yoffset<=1;yoffset++) {
		for(int xoffset=-1;xoffset<=1;xoffset++) {
			// Make sure grid[y][x] + offsets != c
			if ( !(yoffset == 0 && xoffset == 0) ) {
				// Make sure grid[y][x] + offsets is within bounds
				if( (y+yoffset >= 0 && y+yoffset < H) && (x+xoffset >= 0 && x+xoffset < W) ) {
					// found valid location for a cell, confirm this location has a cell
					if( grid[y+yoffset][x+xoffset] != NULL )
						neighbors++;
				}
			}
		}
	}
	return neighbors;
}

/********************
** DEBUG FUNCTIONS **
********************/

// Display cell information
// TODO: Needs .prev support
void printCell(struct cell* c) {
	if (c) {
		if(c->prev)
			printf("grid[%i][%i] <- ", c->prev->y, c->prev->x);
		else
			printf("NULL <- ");

		if (c->next)
			printf("grid[%i][%i] -> grid[%i][%i]\n", c->y, c->x, c->next->y, c->next->x);
		else
			printf("grid[%i][%i] -> NULL\n", c->y, c->x);

	} else {
		printf("printCell(): Cell does not exist\n");
	}
}

// Print all cells in grid
void printAllCells(struct cell* head, struct cell*** grid) {
	struct cell* c = head;

	while(c != NULL) {
		printCell(c);
		c = c->next;
	}
}

