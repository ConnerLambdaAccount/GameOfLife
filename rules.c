// 3. Each living cell with two or three neighbors survives
void exec_rule3(int y, int x, struct cell*** display, struct cell*** buffer) {
	if( display[y][x] == NULL)
		return;

	int neighbors = neighborCount(y, x, display);
	if ( neighbors == 2 || neighbors == 3 ) 
		newCell(y, x, buffer);
}

// 4. Each unpopulated cell with 3 neighbors becomes alive
void exec_rule4(int y, int x, struct cell*** display, struct cell*** buffer) {
	if( display[y][x] != NULL)
		return;

	if( neighborCount(y, x, display) == 3 )
		newCell(y, x, buffer);
}
