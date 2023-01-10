#include "SDL_Screen.hpp"

using namespace std;

int main(){
    SDL_Screen s(1000, 1000, "SDL_Lab", 160);

    int x;
    
    while(s.isRunning()) {

        s.setColor(0, 0, 0, 255);
        s.bg();

        s.setColor(255, 0, 0, 255);
        s.filledCircle(x, s.H() - x, 20);

        x = (x + 2) % s.H();
        
        s.refreshAndDetailsAndEvents(); // refresh the render and add the fps desired delay
    }

    return 0;
}