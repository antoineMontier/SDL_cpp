#include "SDL_Screen.hpp"

using namespace std;

int main(int argc, char **argv){
    SDL_Screen s(1000, 1000, "SDL_Lab", 160);
    TTF_Font * f;
    s.setFont(&f, "Roboto-Medium.ttf", 30);

    while(s.isRunning()){
        

        s.setColor(0, 0, 0, 255);
        s.bg();

        s.setColor(255, 0, 0, 255);

        s.paragraph(200, 400, "hello world\nI'm antoine\na 19yo guy trying to display\n text on multiple\n lines\nusing ttf from SDL2", f);
        s.displayPortions(5, 5);
        s.refreshAndDetailsAndEvents();
    }
    
    TTF_CloseFont(f);
    return 0;
}