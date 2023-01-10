#include "SDL_Screen.hpp"

using namespace std;

int main(){
    SDL_Screen s(1000, 1000, "SDL_Lab", 160);
    TTF_Font * f;
    s.setFont(&f, "Roboto-Medium.ttf", 30);

    
    while(s.isRunning()){


        s.setColor(0, 0, 0, 255);
        s.bg();

        s.setColor(255, 0, 0, 255);
        
        s.filledRect(150, 150, 800, 500);

        s.refreshAndDetailsAndEvents(); // refresh the render and add the fps desired delay
    }
    
    TTF_CloseFont(f);
    return 0;
}