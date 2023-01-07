#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <math.h>


#ifndef SDL_BASICS_HPP
#define SDL_BASICS_HPP

using namespace std;

#define WIDTH 800
#define HEIGHT 600

void openSDL(int x, int y, int mode, const char *name, SDL_Window **w, SDL_Renderer **r);

void closeSDL(SDL_Window **w, SDL_Renderer **r);

#endif