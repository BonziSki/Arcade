#include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "func.h"

void SDL_ExitWithError(char * message){
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void SDL_PrintVersion(){
    SDL_version nb;
    SDL_VERSION(&nb);

    printf("SDL %d.%d.%d \n", nb.major, nb.minor, nb.patch);
}

void SDL_ClearScreen(SDL_Renderer * renderer){

    if (SDL_SetRenderDrawColor(renderer, 120, 0, 120, SDL_ALPHA_OPAQUE)){
        SDL_ExitWithError("Impossible de changer de couleur");
    }

    SDL_Rect FillBlack = {
        .x = 0,
        .y = 0,
        .h = HEIGHT,
        .w = WIDTH
    };

    
    if (SDL_RenderFillRect(renderer, &FillBlack)){
        SDL_ExitWithError("Impossible de clear l'écran");
    }

    SDL_RenderPresent(renderer);
}