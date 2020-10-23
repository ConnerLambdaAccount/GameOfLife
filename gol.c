#include "gol.h"

int main(void) {
	// Create 2 grids for double buffering
	struct cell*** grids[2] = { initGrid(), initGrid() };

	// GLIDER
	/*
	newCell(3, 11, grids[0]);
	newCell(4, 12, grids[0]);
	newCell(5, 10, grids[0]);
	newCell(5, 11, grids[0]);
	newCell(5, 12, grids[0]);
	*/
	
	// 4-8-12-8-4 diamond

	// 4
	newCell(10, 80, grids[0]);
	newCell(10, 81, grids[0]);
	newCell(10, 82, grids[0]);
	newCell(10, 83, grids[0]);

	// 8
	newCell(12, 78, grids[0]);
	newCell(12, 79, grids[0]);
	newCell(12, 80, grids[0]);
	newCell(12, 81, grids[0]);
	newCell(12, 82, grids[0]);
	newCell(12, 83, grids[0]);
	newCell(12, 84, grids[0]);
	newCell(12, 85, grids[0]);

	// 12
	newCell(14, 76, grids[0]);
	newCell(14, 77, grids[0]);
	newCell(14, 78, grids[0]);
	newCell(14, 79, grids[0]);
	newCell(14, 80, grids[0]);
	newCell(14, 81, grids[0]);
	newCell(14, 82, grids[0]);
	newCell(14, 83, grids[0]);
	newCell(14, 84, grids[0]);
	newCell(14, 85, grids[0]);
	newCell(14, 86, grids[0]);
	newCell(14, 87, grids[0]);

	// 8
	newCell(16, 78, grids[0]);
	newCell(16, 79, grids[0]);
	newCell(16, 80, grids[0]);
	newCell(16, 81, grids[0]);
	newCell(16, 82, grids[0]);
	newCell(16, 83, grids[0]);
	newCell(16, 84, grids[0]);
	newCell(16, 85, grids[0]);

	// 4
	newCell(18, 80, grids[0]);
	newCell(18, 81, grids[0]);
	newCell(18, 82, grids[0]);
	newCell(18, 83, grids[0]);
	
	for(int t=0, i=0; ;t++, i++) {
		
		// Set display and buffer grids
		i %= 2;
		struct cell*** display = grids[i];
		struct cell*** buffer = grids[1-i];

		// Print display
		printGrid(display);
		printf("Generations: %i\n", t);

		// Rules of life on display, surviving / new cells sent to buffer
		for(int y=0;y<H;y++) {
			for(int x=0;x<W;x++) {
				//exec_rule1(y, x, display, buffer);
				//exec_rule2(y, x, display, buffer);
				exec_rule3(y, x, display, buffer);
				exec_rule4(y, x, display, buffer);
			}
		}

		// clear display
		clearGrid(display);
		usleep(100000);
	}
}
