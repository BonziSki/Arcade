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
 
void DrawControl(SDL_Renderer * renderer){

}

tetrisCell * CreateCell(int xPos,int yPos){
    tetrisCell * temp = malloc(sizeof(tetrisCell));

    temp->filled=0;
    temp->x=20*xPos+(WIDTH/4+80);
    temp->y=20*yPos+80;
    temp->size=20;
    return temp;

}
tetrisView * CreateView(){
    tetrisView * temp = malloc(sizeof(tetrisView));
    temp->width = 12; //10blocs de largeur + 2 de côté
    temp->heigth = 22; // 20 blocs de largeur + 2 de côté
    temp->Cell=malloc(sizeof(tetrisCell *)*temp->heigth);
    for (int i = 0; i < temp->heigth; i++)
    {
        temp->Cell[i]=malloc(sizeof(tetrisCell)*temp->width);
    }
}
void tetrisViewSetup(tetrisView * tetrisView){

}

void PartialClean(SDL_Renderer * renderer){

    if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE)){
        SDL_ExitWithError("Impossible de changer de couleur");
    }

    SDL_Rect FillBlack = {
        .x = WIDTH/4,
        .y = 0,
        .h = HEIGHT,
        .w = WIDTH
    };


    if (SDL_RenderFillRect(renderer, &FillBlack)){
        SDL_ExitWithError("Impossible de clear l'écran");
    }

    // SDL_RenderPresent(renderer);
}