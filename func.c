#include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> //MAC
#include </opt/homebrew/Cellar/sdl_ttf/2.0.11_2/include/SDL/SDL_ttf.h>
// #include <SDL2/SDL.h>  //Windows
// #include <SDL2/SDL_ttf.h>
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

    if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE)){
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

    // SDL_RenderPresent(renderer);


}

void testScreen(SDL_Renderer * renderer){

    if (SDL_SetRenderDrawColor(renderer, 0, 124, 255, SDL_ALPHA_OPAQUE)){
        SDL_ExitWithError("Impossible de changer de couleur");
    }

    SDL_Rect FillBlack = {
        .x = 0,
        .y = 0,
        .h = HEIGHT,
        .w = WIDTH / 2
    };


    if (SDL_RenderFillRect(renderer, &FillBlack)){
        SDL_ExitWithError("Impossible de clear l'écran");
    }

    SDL_RenderPresent(renderer);
}

void SDL_WriteText(SDL_Renderer * renderer, int x, int y, int w, int h, SDL_Color color, char * text){

    //chargement de la police d'écriture
    TTF_Font * font = NULL;
    
    font = TTF_OpenFont("./ressources/font/ARCADEPI.TTF", 20);

    if(font == NULL){
        SDL_ExitWithError("Chargement de la police d'écriture");
    }

    //création de la surface
    SDL_Surface * surface = NULL;

    surface = TTF_RenderText_Blended(font, text, color);

    if (surface == NULL){
        SDL_ExitWithError("Chargement du texte sur la surface");
    }


    //Création de la texture
    SDL_Texture * texture = NULL;

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (texture == NULL){
        SDL_ExitWithError("Chargement de la texture");
    }


    //Création du rectangle
    SDL_Rect rect = {x, y, w, h};

    //Recopie de la texture sur la window
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    //Mise à jour de la fenêtre
    SDL_RenderPresent(renderer);


    //Free

    //fermeture de la texture
    SDL_DestroyTexture(texture);
    
    //fermeture de la surface
    SDL_FreeSurface(surface);

    //Fermeture de la police
    TTF_CloseFont(font);

}