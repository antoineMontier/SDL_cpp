#ifndef SDL_SCREEN_HPP
#define SDL_SCREEN_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>
#include <vector>



class SDL_Screen{
    
    private:
        int _width;
        int _height;
        SDL_Window *w;
        SDL_Renderer *r;
        const char * title;

        void SDL_ExitWithError(const char *string);

        double distance(double x1, double y1, double x2, double y2);

        bool inTheTriangle(double x1, double y1, double x2, double y2, double x3, double y3, double a, double b);

    public:

        SDL_Screen();
        SDL_Screen(double window_width, double window_height);
        SDL_Screen(const char* window_title);
        SDL_Screen(double window_width, double window_height, const char* window_title);

        bool OpenSDL();

        int getW();
        int getH();

        bool refresh();

        bool freeze(unsigned int ms);

        bool CloseSDL();

        void point(double x, double y);
        void point(double x, double y, double thickness);

        void setColor(int red, int green, int blue, int alpha);
        void setColor(int red, int green, int blue);
        void setColor(int grey);

        void bg();
        void bg(int grey);
        void bg(int red, int green, int blue);

        void updateSize();

        void line(int x1, int y1, int x2, int y2);

        void emptyRect(int x, int y, int size);
        void emptyRect(int x, int y, int width, int height);
        void emptyRect(int x, int y, int width, int height, int rounding);//todo
        void emptyRect(int x, int y, int width, int height, int rounding_top_left, int rounding_top_right, int rounding_bottom_right, int rounding_bottom_left);//todo
        
        void filledRect(int x, int y, int size);
        void filledRect(int x, int y, int width, int height);
        void filledRect(int x, int y, int width, int height, int rounding);//todo
        void filledRect(int x, int y, int width, int height, int rounding_top_left, int rounding_top_right, int rounding_bottom_right, int rounding_bottom_left);//todo

        void filledCircle(int x, int y, int radius);
        void filledCircle(int x, int y, int width, int height);

        void emptyCircle(int x, int y, int radius);
        void emptyCircle(int x, int y, int radius, double thickness);
        void emptyCircle(int x, int y, int width, int height);
        //void emptyCircle(int x, int y, int width, int height, double thickness);

        void filledTriangle(int x1, int y1, int x2, int y2, int x3, int y3);

        void emptyTriangle(int x1, int y1, int x2, int y2, int x3, int y3);

        void filledPolygon(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

        void emptyPolygon(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);


};

#endif
