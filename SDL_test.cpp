

#include "SDL_basics.hpp"

using namespace std;







int main(){

    SDL_Window *w;   // open a window command
    SDL_Renderer *r; // render creation
    std::cout << "SDL window and renderer OK"<<std::endl;

    openSDL(WIDTH, HEIGHT, 0, "SDL c++", &w, &r);
    std::cout << "SDL openning OK" << std::endl;

    SDL_Delay(5000);



    closeSDL(&w, &r);
    std::cout << "Closed SDL successfully" << std::endl;
    return 0;
}