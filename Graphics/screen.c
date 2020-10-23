#include "cellColor.c"

void renderGrid(SDL_Renderer* ren, struct cell*** grid, int colorCode) {
	struct cellColor color = getColorByIndex(colorCode);
	SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, 255);
	for(int y=0;y<H;y++) {
		for(int x=0;x<W;x++) {
			SDL_Rect rect = { .x=x*CELLSIZE, .y=y*CELLSIZE, .w=CELLSIZE, .h=CELLSIZE };
			if(grid[y][x] != NULL) {
				SDL_RenderFillRect(ren, &rect);
			}
		}
	}
}

// may want to change this to  take a rect for grid and only clear that
// and have it render in white, thus removing the need for the else statement in renderGrid
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
	
	char* textArray[] = { genString, "s - Start/Stop", "c - cycle colors", "k - kill cells", "r - randomize", "a - slower", "d - faster", "1 - Load Preset", "2 - Load Preset", "u - rules", "q - quit", };
	
	for(int i=0, y=20;i<11;i++, y += 20) {
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
