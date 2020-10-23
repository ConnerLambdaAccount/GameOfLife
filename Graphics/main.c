#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define RESOLUTION_H 720
#define RESOLUTION_W 1280

#include "mainEventLoop.c"

int main(void) {
	// Initalize SDL & SDL_ttf
	if(SDL_Init(SDL_INIT_VIDEO) != 0) { return -1; }
	if(TTF_Init() != 0) { 
		SDL_Quit();
		return -1; 
	}
	
	// Create Window
	SDL_Window* win = SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, RESOLUTION_W, RESOLUTION_H, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if(!win) {
		TTF_Quit();
		SDL_Quit();
		return -1; 
	}
	
	// Create Renderer
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!ren) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		TTF_Quit();
		SDL_Quit();
		return -1; 
	}
	
	// Run the game of life
	TTF_Font* gameFont = TTF_OpenFont("fonts/DinaRemaster-Bold.ttf", 16);
	mainEventLoop(ren, gameFont);
	
	// Exit
	TTF_CloseFont(gameFont);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	TTF_Quit();
	SDL_Quit();
}
