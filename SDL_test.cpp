#include "SDL_basics.hpp"

using namespace std;


int width, height;


int main(){

    SDL_Window *w;   // open a window command
    SDL_Renderer *r; // render creation
    std::cout << "SDL window and renderer OK"<<std::endl;

    openSDL(WIDTH, HEIGHT, 0, "SDL c++", &w, &r);
    SDL_SetWindowResizable(w, SDL_TRUE);
    std::cout << "SDL openning OK" << std::endl;


    bool program_launched = true;

    while(program_launched){
        SDL_Event evt; // ask events

        SDL_Delay(100);

        SDL_RenderPresent(r); // refresh the render

        while (SDL_PollEvent(&evt))
        { // reads all the events (mouse moving, key pressed...)        //possible to wait for an event with SDL_WaitEvent
            switch (evt.type)
            {
            case SDL_WINDOWEVENT:
                if (evt.window.event == SDL_WINDOWEVENT_RESIZED) {
                    SDL_GetWindowSize(w, &width, &height);
                    printf("MESSAGE:Resizing window... width = %d   height = %d\n", width, height);
                }
                break;
            case SDL_QUIT:
                program_launched = SDL_FALSE; // quit the program if the user closes the window
                break;

            case SDL_KEYDOWN: // SDL_KEYDOWN : hold a key            SDL_KEYUP : release a key
                switch (evt.key.keysym.sym)
                { // returns the key ('0' ; 'e' ; 'SPACE'...)

                case SDLK_ESCAPE:
                    program_launched = SDL_FALSE; // escape the program by pressing esc
                    break;

                default:
                    break;
                }
            default:
                break;
            }
        }

    }



    closeSDL(&w, &r);
    std::cout << "Closed SDL successfully" << std::endl;
    return 0;
}