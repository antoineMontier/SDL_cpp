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

    /*SDL_DisplayMode displayMode;
    if (SDL_GetDesktopDisplayMode(0, &displayMode) != 0)//know actual screen size
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Initialization SDL failed", NULL);*/

    w = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_SetWindowResizable(w, SDL_TRUE);

    r = SDL_CreateRenderer(w, -1, SDL_RENDERER_TARGETTEXTURE);
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);//make alpha transparent

    if (TTF_Init() != 0){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Initialization SDL failed", NULL);
        exit(1);
        return false; // error
    } 
    return true;//sdl opening is succesful
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

void SDL_Screen::SDL_ExitWithError(const char *string)
{
    SDL_Log("Error : %s > %s\n", string, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void SDL_Screen::point(double x, double y){
    if (SDL_RenderDrawPoint(r, x, y) != 0)
        SDL_ExitWithError("failed to draw point");
}

void SDL_Screen::point(double x, double y, double thickness){
    //int thick =  static_cast<int>(round(thickness));
    for(double i = x - thickness/2; i < x + thickness/2 ; i++)
        for(double j = y - thickness/2; j < y + thickness/2 ; j++)
            if (SDL_RenderDrawPoint(r, i, j) != 0)
                SDL_ExitWithError("failed to draw point");
    
}

void SDL_Screen::setColor(int red, int green, int blue, int alpha){
    if (SDL_SetRenderDrawColor(r, red, green, blue, alpha) != 0)
        SDL_ExitWithError("failed to set color");
}

void SDL_Screen::setColor(int red, int green, int blue){
    if (SDL_SetRenderDrawColor(r, red, green, blue, 255) != 0)
        SDL_ExitWithError("failed to set color");
}

void SDL_Screen::setColor(int grey){
    if (SDL_SetRenderDrawColor(r, grey, grey, grey, 255) != 0)
        SDL_ExitWithError("failed to set color");
}

void SDL_Screen::bg(){
    for(int x = -1 ; x < width + 1; x++)
        for(int y = -1 ; y < height + 1; y++)
            point(x, y);
}

void SDL_Screen::bg(int grey){
    //save the renderer color
    Uint8 cr, cg, cb, ca;
    if(SDL_GetRenderDrawColor(r, &cr, &cg, &cb, &ca) != 0)
        SDL_ExitWithError("failed to save color");
    setColor(grey);
    for(int x = -1 ; x < width + 1; x++)
        for(int y = -1 ; y < height + 1; y++)
            point(x, y);
    //reset the color as before
    setColor(cr, cg, cb, ca);
}

void SDL_Screen::bg(int red, int green, int blue){
    //save the renderer color
    Uint8 cr, cg, cb, ca;
    if(SDL_GetRenderDrawColor(r, &cr, &cg, &cb, &ca) != 0)
        SDL_ExitWithError("failed to save color");
    setColor(red, green, blue);
    for(int x = -1 ; x < width + 1; x++)
        for(int y = -1 ; y < height + 1; y++)
            point(x, y);
    //reset the color as before
    setColor(cr, cg, cb, ca);
}


void SDL_Screen::updateSize(){
    int _wi, _he;
    SDL_GetWindowSize(w, &_wi, &_he);
    width = _wi;
    height = _he;
}