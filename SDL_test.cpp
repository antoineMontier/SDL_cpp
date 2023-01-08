#include "SDL_Screen.hpp"

using namespace std;


int width, height;


int main(){

    SDL_Screen s;
    s.OpenSDL();


    bool program_launched = true;

    while(program_launched){
        SDL_Event evt; // ask events

        s.setColor(255, 0, 0, 255);
        s.point(50, 50);
        s.setColor(255, 0, 255, 255);
        s.point(300, 100, 30);
        s.setColor(0, 255, 0, 255);
        s.point(300, 220, 30);
        s.bg(100);
        s.setColor(0, 255, 0, 255);
        s.point(300, 180, 30);


        s.freeze(100);
        s.refresh(); // refresh the render

        while (SDL_PollEvent(&evt))
        { // reads all the events (mouse moving, key pressed...)        //possible to wait for an event with SDL_WaitEvent
            switch (evt.type)
            {
            case SDL_WINDOWEVENT:
                if (evt.window.event == SDL_WINDOWEVENT_RESIZED) {
                    //SDL_GetWindowSize(w, &width, &height);
                    //printf("MESSAGE:Resizing window... width = %d   height = %d\n", width, height);
                }
                break;
            case SDL_QUIT:
                program_launched = false; // quit the program if the user closes the window
                break;

            case SDL_KEYDOWN: // SDL_KEYDOWN : hold a key            SDL_KEYUP : release a key
                switch (evt.key.keysym.sym)
                { // returns the key ('0' ; 'e' ; 'SPACE'...)

                case SDLK_ESCAPE:
                    program_launched = false; // escape the program by pressing esc
                    break;

                default:
                    break;
                }
            default:
                break;
            }
        }

    }



    s.CloseSDL();
    std::cout << "Closed SDL successfully" << std::endl;
    return 0;
}