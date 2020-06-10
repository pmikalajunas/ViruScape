#include "SDL/SDL.h"

int main( int argc, char* args[] )
{
    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    //Quit SDL
    SDL_Quit();

    return 0;
}

// g++.exe -LC:\SDL-1.2.15\lib -o bin\Debug\GameEmpty.exe obj\Debug\main.o  -lmingw32 -lSDLmain -lSDL   -mwindows


//g++.exe -Wall -g -IC:\SDL-1.2.15\include -c C:\Users\Paulius\Documents\C++Exam\GameEmpty\GameEmpty\main.cpp -o obj\Debug\main.o
//g++.exe -LC:\SDL-1.2.15\lib -o bin\Debug\GameEmpty.exe obj\Debug\main.o  -lmingw32 -lSDLmain -lSDL   -mwindows
