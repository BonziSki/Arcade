// #define SDL_MAIN_HANDLED
//MAC
#include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> 
#include </opt/homebrew/Cellar/sdl_ttf/2.0.11_2/include/SDL/SDL_ttf.h>
//Windows
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "menu/menu.h"
#include "func.h"
#include "games/pong/pong.h"


/*
commande de compilation :
MAC : gcc main.c -o prog $(sdl2-config --cflags --libs)
WINDOWS : gcc main.c -o prog.exe -lmingw32 -lSDL2main -lSDL2 
WINDOWS sans terminal : gcc main.c -o prog.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -mwindows
*/


int main(int argc, char **argv){

    SDL_PrintVersion();

    //initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_ExitWithError("Initialisation SDL");
    }

    //initialisation de la gestion du texte
    if (TTF_Init() != 0){
        SDL_ExitWithError("Initialisation TTF");
    }
    
    //programme
    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;

    if(SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) != 0){
        SDL_ExitWithError("Impossible de créer la fenetre et le rendu");
    }

    //chargement de la police d'écriture
    TTF_Font * arcadeFont = NULL;
    
    arcadeFont = TTF_OpenFont("./ressources/font/ARCADEPI.TTF",20);

    if(arcadeFont == NULL){
        SDL_ExitWithError("Chargement de la police d'écriture");
    }

    Pong_Player * p1 = createPongPlayer(1);
    Pong_Player * p2 = createPongPlayer(2);
    Ball * ball = createPongBall();

    
    SDL_Event event;
    int quit = 0;
    mainPongLoop(window, renderer);
    while (!quit){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = 1;
            }
        }
    }
    
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}