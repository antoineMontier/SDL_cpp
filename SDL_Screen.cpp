#include "SDL_Screen.hpp"

using namespace std;

SDL_Screen::SDL_Screen(){
    _width = 600;
    _height = 480;
    title = "SDL_Screen";
}

SDL_Screen::SDL_Screen(double window_width, double window_height){
    _width = window_width;
    _height = window_height;
    title = "SDL_Screen";
}

SDL_Screen::SDL_Screen(const char* window_title){
    _width = 600;
    _height = 480;
    title = window_title;
}

SDL_Screen::SDL_Screen(double window_width, double window_height, const char* window_title){
    _width = window_width;
    _height = window_height;
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

    w = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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

double SDL_Screen::distance(double x1, double y1, double x2, double y2){return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));}


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
    for(int x = -1 ; x < _width + 1; x++)
        for(int y = -1 ; y < _height + 1; y++)
            point(x, y);
}

void SDL_Screen::bg(int grey){
    //save the renderer color
    Uint8 cr, cg, cb, ca;
    if(SDL_GetRenderDrawColor(r, &cr, &cg, &cb, &ca) != 0)
        SDL_ExitWithError("failed to save color");
    setColor(grey);
    for(int x = -1 ; x < _width + 1; x++)
        for(int y = -1 ; y < _height + 1; y++)
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
    for(int x = -1 ; x < _width + 1; x++)
        for(int y = -1 ; y < _height + 1; y++)
            point(x, y);
    //reset the color as before
    setColor(cr, cg, cb, ca);
}


void SDL_Screen::updateSize(){
    int _wi, _he;
    SDL_GetWindowSize(w, &_wi, &_he);
    _width = _wi;
    _height = _he;
}

void SDL_Screen::line(int x1, int y1, int x2, int y2){
    if(SDL_RenderDrawLine(r, x1, y1, x2, y2) != 0)
        SDL_ExitWithError("failed to draw a line");
}

void SDL_Screen::filledRect(int x, int y, int size){
    for(int i = x ; i < x + size; i++)
        for(int j = y ; j < y + size; j++)
            SDL_RenderDrawPoint(r, i, j);
}

void SDL_Screen::filledRect(int x, int y, int width, int height){
    for(int i = x ; i < x + width; i++)
        for(int j = y ; j < y + height; j++)
            SDL_RenderDrawPoint(r, i, j);
}

void SDL_Screen::filledCircle(int x, int y, int radius){
    for(int i = x - radius; i < x + radius; i++)
        for(int j = y - radius; j < y + radius; j++)
            if(distance(i, j, x, y) < radius)
                SDL_RenderDrawPoint(r, i, j);
}