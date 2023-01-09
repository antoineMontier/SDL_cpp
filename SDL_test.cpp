#include "SDL_Screen.hpp"

using namespace std;




int main(){

    SDL_Screen s;
    s.OpenSDL();
    


    bool program_launched = true;
    int x;

    s.setFPS(120);

    while(program_launched){
        SDL_Event evt; // ask events
        

        s.setColor(0, 0, 0, 255);
        
        s.bg();
        
        s.setColor(255, 0, 0, 255);
        s.filledCircle(x, s.getH() - x, 20);
        x = (x + 2) % s.getH();


        
        while (SDL_PollEvent(&evt))
        { // reads all the events (mouse moving, key pressed...)        //possible to wait for an event with SDL_WaitEvent
            switch (evt.type)
            {
            case SDL_WINDOWEVENT:
                if (evt.window.event == SDL_WINDOWEVENT_RESIZED) {
                    s.updateSize();
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

        s.refreshAndDetails(); // refresh the render and add the fps desired delay
    }



    s.CloseSDL();
    std::cout << "Closed SDL successfully" << std::endl;
    return 0;
}