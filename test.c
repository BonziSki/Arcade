#include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h>
#include </opt/homebrew/Cellar/sdl_ttf/2.0.11_2/include/SDL/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>

#include "func.h"



/*
commande de compilation :
MAC :   gcc main.c -o prog $(sdl2-config --cflags --libs)
        gcc main.c func.c ./menu/menu.c -o prog $(sdl2-config --cflags --libs) -lSDL_ttf
*/


int main(int argc, char **argv){


    //initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_ExitWithError("Initialisation SDL");
    }

    //initialisation de la gestion du texte
    if (TTF_Init() != 0){
        SDL_ExitWithError("Initialisation TTF");
    }
    
    //création de la fenêtre
    SDL_Window * window = NULL;
    window = SDL_CreateWindow("test",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 400, 0);

    //vérification de la création de la fenêtre
    if (window == NULL){
        SDL_ExitWithError("Creation de la fenêtre");
    }

    //création du rendu
    SDL_Renderer * renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    //vérification de la création du rendu
    if (renderer == NULL){
        SDL_ExitWithError("Creation de la fenêtre");
    }


    //chargement de la police d'écriture
    TTF_Font * ourFont = NULL;
    
    ourFont = TTF_OpenFont("./ressources/font/ARCADEPI.ttf",20);

    if(ourFont == NULL){
        SDL_ExitWithError("Chargement de la police d'écriture");
    }


    //création de la surface
    SDL_Surface * texte = NULL;
    SDL_Color White = {255, 255, 255};

    texte = TTF_RenderText_Solid(ourFont, "test", White);

    if (texte == NULL){
        SDL_ExitWithError("Chargement du texte");
    }


    //Création de la texture
    SDL_Texture * texture = NULL;

    texture = SDL_CreateTextureFromSurface(renderer, texte);

    if (texture == NULL){
        SDL_ExitWithError("Chargement de la texture");
    }


    // //Création du rectangle
    // SDL_Rect rect = {0, 0, 800, 400};

    // //Recopie de la texture sur la window
    // SDL_RenderCopy(renderer, texture, NULL, &rect);

    // //Mise à jour de la fenêtre
    // SDL_RenderPresent(renderer);
    

//--------------------------
    // SDL_ClearScreen();

    SDL_Event event;
    int quit = 0;
    while (!quit){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = 1;
            }
        }
    }

    //fermeture de la texture
    SDL_DestroyTexture(texture);
    
    //fermeture de la surface
    SDL_FreeSurface(texte);

    //Fermeture de la police
    TTF_CloseFont(ourFont);

    //Fermeture de TTF
    TTF_Quit();

    //Fermeture de la fenêtre
    SDL_DestroyRenderer(renderer);

    //Fermeture de la fenêtre
    SDL_DestroyWindow(window);

    //Fermeture de SDL
    SDL_Quit();

    return EXIT_SUCCESS;
}