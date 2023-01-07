#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

using namespace std;



void openSDL(int x, int y, int mode, const char *name, SDL_Window **w, SDL_Renderer **r)
{

    if (0 != SDL_Init(/*flag*/ SDL_INIT_VIDEO | SDL_INIT_EVENTS)){ // lots of flags like SDL_INIT_AUDIO ; *_VIDEO ; *_EVEhTHING... To separe with '|'
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Initialization SDL failed", NULL);
        exit(1);
    }   
    // at this point, the SDL is well initialised, we can afford it because of the if

    *w = SDL_CreateWindow(name, x, y, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    *r = SDL_CreateRenderer(*w, -1, 1);

    if (TTF_Init() != 0){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Initialization SDL failed", NULL);
        exit(1);
    } 
}

void closeSDL(SDL_Window **w, SDL_Renderer **r)
{
    TTF_Quit();
    SDL_DestroyRenderer(*r);
    SDL_DestroyWindow(*w);
    SDL_Quit();
}



int main(){

    std::cout << "hey"<<std::endl;

    return 0;
}