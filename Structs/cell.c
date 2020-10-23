#include <stdlib.h>
struct cell {
	int y;
	int x;
};

void newCell(int y, int x, struct cell ***grid) {
	struct cell newCell = { .y=y, .x=x };
	grid[y][x] = malloc(sizeof(struct cell));
	*grid[y][x] = newCell;
}

void remCell(int y, int x, struct cell*** grid) {
	free(grid[y][x]);
	grid[y][x] = NULL;
}

int neighborCount(int y, int x, struct cell*** grid) {
	int neighbors = 0;
	for(int yoffset=-1;yoffset<=1;yoffset++) {
		for(int xoffset=-1;xoffset<=1;xoffset++) {
			if ( !(yoffset == 0 && xoffset == 0) ) {
				if( (y+yoffset >= 0 && y+yoffset < H) && (x+xoffset >= 0 && x+xoffset < W) ) {
					if( grid[y+yoffset][x+xoffset] != NULL )
						neighbors++;
				}
			}
		}
	}
	return neighbors;
}
