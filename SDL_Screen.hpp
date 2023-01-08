#ifndef SDL_SCREEN_HPP
#define SDL_SCREEN_HPP

#include "SDL_basics.hpp"
#include <cmath>




class SDL_Screen{
    
    private:
        double height;
        double width;
        SDL_Window *w;
        SDL_Renderer *r;
        const char * title;
        SDL_Event e;

        void SDL_ExitWithError(const char *string);

    public:

        SDL_Screen();
        SDL_Screen(double window_width, double window_height);
        SDL_Screen(const char* window_title);
        SDL_Screen(double window_width, double window_height, const char* window_title);

        bool OpenSDL();

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
        
};

#endif
