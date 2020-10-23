/*
	POPULATED CELLS
*/

// 1. Each cell with one or no neighbors dies
void exec_rule1(int y, int x, struct cell*** display, struct cell*** buffer) {
	if( display[y][x] == NULL)
		return;

	if( !(neighborCount(y, x, display) <= 1) )
		newCell(y, x, buffer);
}

// 2. Each cell with four or more neighbors dies
void exec_rule2(int y, int x, struct cell*** display, struct cell*** buffer) {
	if( display[y][x] == NULL)
		return;
	if( !(neighborCount(y, x, display) >= 4) )
		newCell(y, x, buffer);
}

// 3. Each cell with two or three neighbors survives
void exec_rule3(int y, int x, struct cell*** display, struct cell*** buffer) {
	if( display[y][x] == NULL)
		return;

	int neighbors = neighborCount(y, x, display);
	if ( neighbors == 2 || neighbors == 3 ) 
		newCell(y, x, buffer);
}

/*
	UNPOPULATED CELLS
*/

// 4. Each cell with 3 neighbors becomes alive
void exec_rule4(int y, int x, struct cell*** display, struct cell*** buffer) {
	if( display[y][x] != NULL)
		return;

	if( neighborCount(y, x, display) == 3 )
		newCell(y, x, buffer);
}
