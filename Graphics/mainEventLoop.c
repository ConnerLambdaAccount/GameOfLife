#include "../gol.h"

#include "screen.c"
#include "presets.c"

void mainEventLoop(SDL_Renderer* ren, TTF_Font* gameFont) {
	// Removes red default flash by rendering first
	clearScreen(ren);
	SDL_RenderPresent(ren);

	// Create 2 grids for double buffering
	struct cell*** grids[2] = { initGrid(), initGrid() };
	
	// Load 4-8-12-8-4 diamond
	loadPresetDiamond(grids[0]);

	int quit = 0;
	int paused = 1;
	int cellColor = 0;
	int generations = 0;
	int ms_delay = 64;

	while(!quit) {
		// Set grid to display, and grid to act as buffer
		struct cell*** display = grids[generations % 2];
		struct cell*** buffer = grids[1 - (generations % 2)];

		// Render the display grid & controls list
		clearScreen(ren);
		renderGrid(ren, display, cellColor);
		renderControls(ren, gameFont, generations, ms_delay);
		SDL_RenderPresent(ren);

		// Poll for input
		SDL_Event e;
		while(SDL_PollEvent(&e) && !quit) {
			// Keyboard input
			if(e.type == SDL_KEYDOWN) {
				switch(e.key.keysym.sym) {
					// Quit
					case SDLK_q:
						quit = 1;
						break;
					// Start / Stop
					case SDLK_s:
						paused = !paused;
						break;
					// Rules
					case SDLK_u:
						paused = 1;
						//renderRulesPopup();
						//present renderer
						break;
					// Kill all cells
					case SDLK_k:
						clearGrid(display);
						generations = 0;
						break;
					// Randomize cells
					case SDLK_r:
						randomizeGrid(display);
						generations = 0;
						break;
					// Cycle cell color
					case SDLK_c:
						cellColor++;
						break;
					// Slow simulation speed
					case SDLK_a:
						if(ms_delay + 32 <= 320)
							ms_delay += 32;
						break;
					// Increase simulation speed
					case SDLK_d:
						if(ms_delay - 32 >= 32)
							ms_delay -= 32;
						break;
					// Step ahead one generation (Game must be paused)
					case SDLK_n:
						if(paused) {
							// Rules of life on display grid / buffer will be displayed next iteration
							for(int y=0;y<H;y++) {
								for(int x=0;x<W;x++) {
									exec_rule3(y, x, display, buffer);
									exec_rule4(y, x, display, buffer);
								}
							}
							clearGrid(display);
							generations++;
						}
						break;
					case SDLK_1:
						loadPresetGlider(display);
						generations = 0;
						break;
					case SDLK_2:
						loadPresetDiamond(display);
						generations = 0;
						break;
				}
			}

			// Mouse Input
			if(e.type == SDL_MOUSEBUTTONDOWN) {
				int x = (e.button.x - (e.button.x % CELLSIZE))/CELLSIZE;
				int y = (e.button.y - (e.button.y % CELLSIZE))/CELLSIZE;
				if(display[y][x])
					remCell(y, x, display);
				else
					newCell(y, x, display);
			}
			
			// Scroll to scale cell size
			if(e.type == SDL_MOUSEWHEEL) {
				if(e.wheel.y > 0) {
					// Scroll up
				} else {
					// Scroll down
				}
			}
		}
		
		if(!paused) {
			// Rules of life on display grid / buffer will be displayed next iteration
			for(int y=0;y<H;y++) {
				for(int x=0;x<W;x++) {
					exec_rule3(y, x, display, buffer);
					exec_rule4(y, x, display, buffer);
				}
			}
			clearGrid(display);
			generations++;
		}
		SDL_Delay(ms_delay);
	}

	// Free grid memory
	clearGrid(grids[0]);
	clearGrid(grids[1]);
	freeGrid(grids[0]);
	freeGrid(grids[1]);
	// Main() will finish now, free()ing SDL-related memory...
}
