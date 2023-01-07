#include "SDL_Screen.hpp"

using namespace std;

SDL_Screen::SDL_Screen(){
    width = 600;
    height = 480;
    title = "SDL_Screen";
}

SDL_Screen::SDL_Screen(double window_width, double window_height){
    width = window_width;
    height = window_height;
    title = "SDL_Screen";
}

SDL_Screen::SDL_Screen(const char* window_title){
    width = 600;
    height = 480;
    title = window_title;
}

SDL_Screen::SDL_Screen(double window_width, double window_height, const char* window_title){
    width = window_width;
    height = window_height;
    title = window_title;
}

bool SDL_Screen::OpenSDL(){

    if (0 != SDL_Init(/*flag*/ SDL_INIT_VIDEO | SDL_INIT_EVENTS)){ // lots of flags like SDL_INIT_AUDIO ; *_VIDEO ; *_EVEhTHING... To separe with '|'
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Initialization SDL failed", NULL);
        exit(1);
        return false; // error
    }   
    // at this point, the SDL is well initialised, we can afford it because of the if

    w = SDL_CreateWindow(title, width, height, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    r = SDL_CreateRenderer(w, -1, 1);

    SDL_SetWindowResizable(w, SDL_TRUE);

    if (TTF_Init() != 0){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Initialization SDL failed", NULL);
        exit(1);
        return false; // error
    } 
    return true;//everything is succesful
}

bool SDL_Screen::CloseSDL(){
    TTF_Quit();
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    SDL_Quit();
    return 1;
}

bool SDL_Screen::refresh(){
    SDL_RenderPresent(r);
    return true;
}

bool SDL_Screen::freeze(unsigned int ms){
    SDL_Delay(ms);
    return true;
}