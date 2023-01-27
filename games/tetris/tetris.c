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
    int score=0;
    int quit =0;
    DrawControl(renderer);
    int ** tempArray = createTmpTable(HEIGTH_TABLE,WIDTH_TABLE);
    int ** permArray = createPermTable(HEIGTH_TABLE,WIDTH_TABLE);
    while (!quit)
    {
        updateTetris(tempArray,permArray,HEIGTH_TABLE,WIDTH_TABLE,&score);
        DrawGame(renderer);
        DrawScore(renderer,score);
        DrawNext(renderer);
    }
}


void DrawScore(SDL_Renderer * renderer,int score){

}
void DrawNext(SDL_Renderer * renderer){

}
void DrawControl(SDL_Renderer * renderer){

}

void DrawGame(SDL_Renderer * renderer){
    PartialClean(renderer);
    //print tableau permanent 
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));
    if (SDL_SetRenderDrawColor(renderer, 255, 0,0, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }
    rect->w = 80;
    rect->h = 80;
    rect->y = 280;
    rect->x = 280;
        SDL_RenderFillRect(renderer, rect);
    SDL_RenderPresent(renderer);


    // print tableau temporaire


    // clean tableau temporaire
}