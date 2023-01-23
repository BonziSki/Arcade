//MAC
// #include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> 
// #include </opt/homebrew/Cellar/sdl_ttf/2.0.11_2/include/SDL/SDL_ttf.h>
//Windows
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "tetris.h"
#include "../../func.h"
#include "../../menu/menu.h"
 
void MainTetrisLoop(SDL_Window * window, SDL_Renderer * renderer){
    SDL_ClearScreen(renderer);
    int quit =0;
    DrawControl(renderer);

    while (!quit)
    {
        void DrawGame(renderer);
    }
    

}


void DrawScore(SDL_Renderer * renderer){

}
void DrawNext(SDL_Renderer * renderer){

}

void DrawGame(SDL_Renderer * renderer){
    PartialClean(renderer);
    
}