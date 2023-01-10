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
        long _ms;
        SDL_Window *w;
        SDL_Renderer *r;
        SDL_Event e;
        const char * title;
        double _fps;
        double fps_max = 180;
        static bool instanceExist;

        void SDL_ExitWithError(const char *string);

        double distance(double x1, double y1, double x2, double y2);

        bool inTheTriangle(double x1, double y1, double x2, double y2, double x3, double y3, double a, double b);

    public:

        /// @brief creates a screen of 600*480 entitled "SDL_Screen" with 30 fps and Open SDL (initialisation)
        SDL_Screen();
        /// @brief creates a screen entitled "SDL_Screen" with 30 fps
        /// @param window_width width of the screen
        /// @param window_height height of the screen
        SDL_Screen(double window_width, double window_height);
        /// @brief creates a screen entitled "SDL_Screen" and Open SDL (initialisation)
        /// @param window_width width of the screen
        /// @param window_height height of the screen
        /// @param fps frames per second
        SDL_Screen(double window_width, double window_height, double fps);
        /// @brief creates a screen of 600*480 with 30 fps and Open SDL (initialisation)
        /// @param window_title title of the new screen
        SDL_Screen(const char* window_title);
        /// @brief creates a screen with 30 fps
        /// @param window_width width of the screen
        /// @param window_height height of the screen
        /// @param window_title title of the screen
        SDL_Screen(double window_width, double window_height, const char* window_title);
        /// @brief creates a screen and Open SDL (initialisation)
        /// @param window_width width of the screen
        /// @param window_height height of the screen
        /// @param window_title title of the screen
        /// @param fps frames per second
        SDL_Screen(double window_width, double window_height, const char* window_title, double fps);

        /// @brief Quit SDL, prints if it's a success or not in the cout
        ~SDL_Screen();

        bool OpenSDL();

        int W();
        int H();
        double getFPS();

        bool refresh();
        bool refreshAndDetails();

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
        void emptyRect(int x, int y, int width, int height, int rounding);
        void emptyRect(int x, int y, int width, int height, int rounding_top_left, int rounding_top_right, int rounding_bottom_right, int rounding_bottom_left);//todo
        
        void filledRect(int x, int y, int size);
        void filledRect(int x, int y, int width, int height);
        void filledRect(int x, int y, int width, int height, int rounding);
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

        bool setFPS(double fps);
};

#endif
