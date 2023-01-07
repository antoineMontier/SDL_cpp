#ifndef SDL_SCREEN_HPP
#define SDL_SCREEN_HPP

#include "SDL_basics.hpp"




class SDL_Screen{
    
    private:
        double height;
        double width;
        SDL_Window *w;
        SDL_Renderer *r;
        const char * title;

    public:

        SDL_Screen();

        SDL_Screen(double window_width, double window_height);

        SDL_Screen(const char* window_title);

        SDL_Screen(double window_width, double window_height, const char* window_title);

        bool OpenSDL();

        bool refresh();

        bool freeze(unsigned int ms);

        bool CloseSDL();
};

#endif
