# SDL in C++

## Project Architecture

```sh
│ 
├── Makefile
├── README.md
├── Roboto-Medium.ttf
├── SDL_Screen.cpp
├── SDL_Screen.hpp
└── SDL_test.cpp
```

## What is SDL

SDL is a library used for screen/keyboard/sound and mouse interactions.

## Goal

My goal is to provide a simple interface to SDL functions for me and everyone who would like to use it for a GUI

## Use : 

Here is a simple example of how to use my SDL library : 

```cpp
#include "SDL_Screen.hpp"

using namespace std;

int main(int argc, char **argv){

    SDL_Screen s(1000, 1000, "SDL_Lab", 160); // creates the object

    while(s.isRunning()){   // starts the loop

        s.setColor(128, 56, 256, 128);  // set the drawing color
        s.filledCircle(s.W()/2, s.H()/2, 50); // draws a circle
        s.refresh(); // apply changes on screen
        s.events(...); // update event coordination

    }

    return 0;
}
```
