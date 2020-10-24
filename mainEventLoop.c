#include "cell.c"
#include "grid.c"
#include "rules.c"
#include "screen.c"
#include "presets.c"

void mainEventLoop(SDL_Renderer* ren, TTF_Font* gameFont) {
	// Removes red default flash by grey screen before anything else
    SDL_SetRenderDrawColor(ren, 170, 177, 189, 255);
    SDL_RenderFillRect(ren, NULL);
	SDL_RenderPresent(ren);

	// Create 2 grids for double buffering
	int h = 90;
	int w = 136;
	int cellPixelSize = 8;
	struct cell*** grids[2] = { initGrid(h, w), initGrid(h, w) };

	int quit = 0;
	int paused = 1;
	int cellColor = 0; 		 // Index of selected color, will modulo 6 in renderGrid
	int generations = 0;
	int ms_delay = 64;		// millisecond delay between rendering

	while(!quit) {
		// Set grid to display, and grid to act as buffer
		struct cell*** display = grids[generations % 2];
		struct cell*** buffer = grids[1 - (generations % 2)];

		// Render the display grid & controls list
		clearScreen(ren);
		renderGrid(ren, cellPixelSize, h, w, display, cellColor);
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
						renderRules(ren);
						SDL_RenderPresent(ren);
						break;
					// Kill all cells
					case SDLK_k:
						clearGrid(h, w, display);
						generations = 0;
						break;
					// Randomize cells
					case SDLK_r:
						randomizeGrid(h, w, display);
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
							for(int y=0;y<h;y++) {
								for(int x=0;x<w;x++) {
									exec_rule3(y, x, h, w, display, buffer);
									exec_rule4(y, x, h, w, display, buffer);
								}
							}
							clearGrid(h, w, display);
							generations++;
						}
						break;
					case SDLK_1:
						clearGrid(h, w, display);
						loadPresetGlider(display);
						generations = 0;
						break;
					case SDLK_2:
						clearGrid(h, w, display);
						loadPresetDiamond(display);
						generations = 0;
						break;
				}
			}

			// Mouse Input
			if(e.type == SDL_MOUSEBUTTONDOWN) {
				int x = (e.button.x - (e.button.x % cellPixelSize))/cellPixelSize;
				int y = (e.button.y - (e.button.y % cellPixelSize))/cellPixelSize;
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
			for(int y=0;y<h;y++) {
				for(int x=0;x<w;x++) {
					exec_rule3(y, x, h, w, display, buffer);
					exec_rule4(y, x, h, w, display, buffer);
				}
			}
			clearGrid(h, w, display);
			generations++;
		}
		SDL_Delay(ms_delay);
	}

	// Free grid memory
	clearGrid(h, w, grids[0]);
	clearGrid(h, w, grids[1]);
	freeGrid(h, grids[0]);
	freeGrid(h, grids[1]);
	// main() will finish now, free()ing SDL-related memory...
}
