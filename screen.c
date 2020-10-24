#include "cellColor.c"

void renderGrid(SDL_Renderer* ren, int cellPixelSize, int h, int w, struct cell*** grid, int colorCode) {
	struct cellColor color = getColorByIndex(colorCode);
	SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, 255);
	for(int y=0;y<h;y++) {
		for(int x=0;x<w;x++) {
			SDL_Rect rect = { .x=x*cellPixelSize, .y=y*cellPixelSize, .w=cellPixelSize, .h=cellPixelSize };
			if(grid[y][x] != NULL) {
				SDL_RenderFillRect(ren, &rect);
			}
		}
	}
}

// Fill entire screen with grey color
void clearScreen(SDL_Renderer* ren) {
	SDL_SetRenderDrawColor(ren, 170, 177, 189, 255);
    SDL_RenderFillRect(ren, NULL);
}

void renderControls(SDL_Renderer* ren, TTF_Font* font, int generations, int delay) {
	SDL_Rect rect = { .x=1088, .y=0, .w=192, .h=720 };
	SDL_SetRenderDrawColor(ren, 20, 92, 86, 255);
	SDL_RenderFillRect(ren, &rect);
	
	// Prepare black font color
	SDL_Color fontColor = { 185, 185, 185 };
	
	// Generations: i
	char genString[64];
	snprintf(genString, 64, "Generations: %i (%i ms)", generations, delay);
	
	char* textArray[] = { genString, "s - Start/Stop", "n - Step Forward", "c - Cycle Colors", "k - Kill Cells", "r - Randomize", "a - Slower", "d - Faster", "1 - Load Glider", "2 - Load Diamond", "u - Rules", "q - Quit", };
	
	for(int i=0, y=20;i<12;i++, y += 20) {
		SDL_Surface* s = TTF_RenderText_Solid(font, textArray[i], fontColor);
		SDL_Texture* t = SDL_CreateTextureFromSurface(ren, s);
		int w, h;
		SDL_QueryTexture(t, NULL, NULL, &w, &h);
		SDL_Rect d = { 1100, y, w, h };
		SDL_RenderCopy(ren, t, NULL, &d);
		SDL_DestroyTexture(t);
		SDL_FreeSurface(s);
	}
}

void renderRules(SDL_Renderer* ren) {
	char* rulesArray[] = { "1. For a cell to survive, it must have 2-3 neighbors", "2. For an unpopulated cell to be populated, it must have 3 neighbors" };
}
