#include "SDL_Screen.hpp"

using namespace std;

SDL_Screen::SDL_Screen(){
    _width = 600;
    _height = 480;
    title = "SDL_Screen";
    _fps = 30.0;
    _ms = 0;
}

SDL_Screen::SDL_Screen(double window_width, double window_height){
    _width = window_width;
    _height = window_height;
    title = "SDL_Screen";
    _fps = 30.0;
    _ms = 0;
}

SDL_Screen::SDL_Screen(const char* window_title){
    _width = 600;
    _height = 480;
    title = window_title;
    _fps = 30.0;
    _ms = 0;
}

SDL_Screen::SDL_Screen(double window_width, double window_height, const char* window_title){
    _width = window_width;
    _height = window_height;
    title = window_title;
    _fps = 30.0;
    _ms = 0;
}

SDL_Screen::SDL_Screen(double window_width, double window_height, double fps){
    _width = window_width;
    _height = window_height;
    title = "SDL_Screen";
    _fps = fps;
    _ms = 0;
}

SDL_Screen::SDL_Screen(double window_width, double window_height, const char* window_title, double fps){
    _width = window_width;
    _height = window_height;
    title = window_title;
    _fps = fps;
    _ms = 0;
}

double SDL_Screen::getFPS(){return _fps;}


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
    if(SDL_GetTicks() - _ms < _fps)
        SDL_Delay(1000.0/_fps - (SDL_GetTicks() - _ms));//add ticks to get a the desired fps
    SDL_RenderPresent(r);//display
    _ms = SDL_GetTicks();//get the ticks for another turn
    return true;
}

bool SDL_Screen::refreshAndDetails(){
    std::cout << "calc ticks : " << (SDL_GetTicks() - _ms);
    long freezed = SDL_GetTicks();
    if(SDL_GetTicks() - _ms < _fps)
        SDL_Delay(1000.0/_fps - (SDL_GetTicks() - _ms));//add ticks to get a the desired fps
    std::cout << "\tfreeze ticks : " << (SDL_GetTicks() - freezed);
    SDL_RenderPresent(r);//display
    std::cout << "\ttotal : " << (SDL_GetTicks() - _ms) << std::endl; 
    _ms = SDL_GetTicks();//get the ticks for another turn
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
    SDL_RenderClear(r);
}

void SDL_Screen::bg(int grey){
    //save the renderer color
    Uint8 cr, cg, cb, ca;
    if(SDL_GetRenderDrawColor(r, &cr, &cg, &cb, &ca) != 0)
        SDL_ExitWithError("failed to save color");
    setColor(grey);
    SDL_RenderClear(r);
    //reset the color as before
    setColor(cr, cg, cb, ca);
}

void SDL_Screen::bg(int red, int green, int blue){
    //save the renderer color
    Uint8 cr, cg, cb, ca;
    if(SDL_GetRenderDrawColor(r, &cr, &cg, &cb, &ca) != 0)
        SDL_ExitWithError("failed to save color");
    setColor(red, green, blue);
    SDL_RenderClear(r);
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

void SDL_Screen::emptyCircle(int x, int y, int radius){
    for(int i = x - radius - 1; i < x + radius + 1; i++)
        for(int j = y - radius - 1; j < y + radius + 1; j++)
            if(distance(i, j, x, y) < radius + 1 && distance(i, j, x, y) > radius - 1)
                SDL_RenderDrawPoint(r, i, j);
}

void SDL_Screen::emptyCircle(int x, int y, int radius, double thickness){
    for(int i = x - radius - thickness; i < x + radius + thickness; i++)
        for(int j = y - radius - thickness; j < y + radius + thickness; j++)
            if(distance(i, j, x, y) < radius + thickness && distance(i, j, x, y) > radius - thickness)
                SDL_RenderDrawPoint(r, i, j);
}

void SDL_Screen::filledCircle(int x, int y, int width, int height){
    int xc = 0;
    int yc = height;
    long a2 = width * width;
    long b2 = height * height;
    long t = -a2 * yc;
    long dxt = 2*b2 * xc;
    long dyt = -2*a2 *yc;

    while (yc >= 0 && xc <= width)
    {
        SDL_RenderDrawLine(r, x - xc, y - yc, x + xc, y - yc);
        SDL_RenderDrawLine(r, x - xc, y + yc, x + xc, y + yc);
        
        if (t + b2 * xc <= -(a2/4+width % 2 + b2) || t + a2 * yc <= -(b2/4+height % 2)){
            xc++;
            dxt+= 2*b2;
            t += dxt;
        }
        else if (t - a2 * yc > -(b2/4+height % 2 + a2)){
            yc--;
            dyt += 2*a2;
            t += dyt;
        }
        else{
            xc++;
            dxt += 2*b2;
            t += dxt;
            yc--;
            dyt += 2*a2;
            t += dyt;
        }
    }
}

void SDL_Screen::emptyCircle(int x, int y, int width, int height){
    int xc = 0;
    int yc = height;
    long a2 = width * width;
    long b2 = height * height;
    long t = -a2 * yc;
    long dxt = 2*b2 * xc;
    long dyt = -2*a2 *yc;

    while (yc >= 0 && xc <= width){

        SDL_RenderDrawPoint(r, x + xc, y + yc);
        SDL_RenderDrawPoint(r, x - xc, y + yc);
        SDL_RenderDrawPoint(r, x + xc, y - yc);
        SDL_RenderDrawPoint(r, x - xc, y - yc);

        if (t + b2 * xc <= -(a2/4+width % 2 + b2) || t + a2 * yc <= -(b2/4+height % 2)){
            xc++;
            dxt+= 2*b2;
            t += dxt;
        }
        else if (t - a2 * yc > -(b2/4+height % 2 + a2)){
            yc--;
            dyt += 2*a2;
            t += dyt;
        }
        else{
            xc++;
            dxt += 2*b2;
            t += dxt;
            yc--;
            dyt += 2*a2;
            t += dyt;
        }
    }
}

int SDL_Screen::getW(){return _width;}

int SDL_Screen::getH(){return _height;}

void SDL_Screen::filledTriangle(int x1, int y1, int x2, int y2, int x3, int y3){
    double s_x = fmin(x1, fmin(x2, x3));
    double s_y = fmin(y1, fmin(y2, y3));
    double f_x = fmax(x1, fmax(x2, x3));
    double f_y = fmax(y1, fmax(y2, y3));
    for (double a = s_x; a <= f_x; a++)
        for (double b = s_y; b <= f_y; b++)
            if (inTheTriangle(x1, y1, x2, y2, x3, y3, a, b))
                SDL_RenderDrawPoint(r, a, b);
}

void SDL_Screen::emptyTriangle(int x1, int y1, int x2, int y2, int x3, int y3){
    SDL_RenderDrawLine(r, x1, y1, x2, y2);
    SDL_RenderDrawLine(r, x3, y3, x2, y2);
    SDL_RenderDrawLine(r, x1, y1, x3, y3);
}

bool SDL_Screen::inTheTriangle(double x1, double y1, double x2, double y2, double x3, double y3, double a, double b){
    int sign1 = -1, sign2 = -1, sign3 = -1;
    if (((x2 - x1) * (b - y1) - (y2 - y1) * (a - x1)) >= 0)
        sign1 = 1;

    if (((x3 - x2) * (b - y2) - (y3 - y2) * (a - x2)) >= 0)
        sign2 = 1;

    if (((x1 - x3) * (b - y3) - (a - x3) * (y1 - y3)) >= 0)
        sign3 = 1;

    if (sign1 == sign2 && sign2 == sign3)
        return true;
    return false;
}

void SDL_Screen::filledPolygon(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
    filledTriangle(x1, y1, x2, y2, x3, y3);
    filledTriangle(x2, y2, x3, y3, x4, y4);
    filledTriangle(x3, y3, x4, y4, x1, y1);
    filledTriangle(x4, y4, x1, y1, x2, y2);
}

void SDL_Screen::emptyPolygon(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
    SDL_RenderDrawLine(r, x1, y1, x2, y2);
    SDL_RenderDrawLine(r, x2, y2, x3, y3);
    SDL_RenderDrawLine(r, x3, y3, x4, y4);
    SDL_RenderDrawLine(r, x4, y4, x1, y1);
}

void SDL_Screen::emptyRect(int x, int y, int size){
    SDL_RenderDrawLine(r, x, y, x + size, y);
    SDL_RenderDrawLine(r, x, y, x, y + size);
    SDL_RenderDrawLine(r, x + size, y + size, x, y + size);
    SDL_RenderDrawLine(r, x + size, y + size, x + size, y);
}

void SDL_Screen::emptyRect(int x, int y, int width, int height){
    SDL_RenderDrawLine(r, x, y, x+width, y);
    SDL_RenderDrawLine(r, x, y, x, y+height);
    SDL_RenderDrawLine(r, x+width, y+height, x+width, y);
    SDL_RenderDrawLine(r, x+width, y+height, x, y+height);
}

void SDL_Screen::filledRect(int x, int y, int width, int height, int rounding){
    //first let's fix the rounding if it's bellow 0 or greater than the half of the smallest side of the rectangle
    if(rounding <= 0){
        filledRect(x, y, width, height);
        return;
    }
    if(rounding > fmin(width, height)/2.0)
        rounding = fmin(width, height)/2.0;
    //let's draw the core rectangles
    filledRect(x, y + rounding, width, height-2*rounding);
    filledRect(x + rounding, y, width-2*rounding, height);

    //draw the 4 corners

    filledCircle(x +  rounding, y + rounding, rounding);//top left
    filledCircle(x + width - rounding, y + rounding, rounding);//top right
    filledCircle(x + rounding, y + height - rounding, rounding);//bottom left
    filledCircle(x + width - rounding, y + height - rounding, rounding);//bottom right
}

void SDL_Screen::emptyRect(int x, int y, int width, int height, int rounding){
    //first let's fix the rounding if it's bellow 0 or greater than the half of the smallest side of the rectangle
    if(rounding <= 0){
        emptyRect(x, y, width, height);
        return;
    }
    if(rounding > fmin(width, height)/2.0)
        rounding = fmin(width, height)/2.0;
    //draw the lines without corners
    double thick = 0.6;
    SDL_RenderDrawLine(r, x + rounding - 1, y, x + width - rounding + 1, y);//top
    SDL_RenderDrawLine(r, x + rounding - 1, y + height, x + width - rounding + 1, y + height);//bottom
    SDL_RenderDrawLine(r, x, y + rounding - 1, x, y + height - rounding + 1);//left
    SDL_RenderDrawLine(r, x + width, y + rounding - 1, x + width, y + height - rounding + 1);//right
    //now draw the four corners

    //==== top left ====
    for(int i = x - thick ; i < x + rounding + thick; i++)
        for(int j = y - thick; j < y + rounding + thick; j++)
            if(distance(x + rounding, y + rounding, i, j) <= rounding + thick && distance(x + rounding, y + rounding, i, j) >= rounding - thick)
                SDL_RenderDrawPoint(r, i, j);
    
    //==== top right ====
    for(int i = x + width - rounding - thick; i < x + width + thick; i++)
        for(int j = y - thick ; j < y + rounding + thick ; j++)
            if(distance(x + width - rounding, y + rounding, i, j) >= rounding - thick && distance(x + width - rounding, y + rounding, i, j) <= rounding + thick) 
                SDL_RenderDrawPoint(r, i, j);

    //==== bottom left ====
    for(int i = x - thick; i < x + rounding + thick; i++)
        for(int j = y + height - rounding - thick; j < y + height + thick; j++)
            if(distance(x + rounding, y + height - rounding, i, j) >= rounding - thick && distance(x + rounding, y + height - rounding, i, j) <= rounding + thick) 
                SDL_RenderDrawPoint(r, i, j);

    //==== bottom right ====
    for(int i = x + width - rounding - thick; i < x + width + thick; i++)
        for(int j = y + height - rounding - thick; j < y + height + thick; j++)
            if(distance(x + width - rounding, y + height - rounding, i, j) <= rounding + thick && distance(x + width - rounding, y + height - rounding, i, j) >= rounding - thick)
                SDL_RenderDrawPoint(r, i, j);
}

void SDL_Screen::setFPS(double fps){_fps = fps;}
