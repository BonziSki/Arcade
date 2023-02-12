#define SDL_MAIN_HANDLED
//MAC
// #include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> 
// #include </opt/homebrew/Cellar/sdl_ttf/2.0.11_2/include/SDL/SDL_ttf.h>
//Windows
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "menu/menu.h"
#include "func.h"
#include "games/snake/snake.h"


/*
commande de compilation :
MAC :   gcc main.c -o prog $(sdl2-config --cflags --libs)
        gcc main.c func.c ./menu/menu.c -o prog $(sdl2-config --cflags --libs) -lSDL_ttf
WINDOWS : gcc main.c -o prog.exe -lmingw32 -lSDL2main -lSDL2 
WINDOWS sans terminal : gcc main.c func.c games/snake/snake.c -o prog.exe -I include -L lib -lmingw32 -lSDL2main -lSDL2 -mwindows
*/


int main(int argc, char **argv){

    srand(time(NULL));

    SDL_PrintVersion();

    //initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_ExitWithError("Initialisation SDL");
    }
    
    //programme
    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;

    if(SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) != 0){
        SDL_ExitWithError("Impossible de créer la fenetre et le rendu");
    }
    SDL_SetWindowTitle(window,"JEUX");



    int quit = 0;
    SDL_Event event;

    mainLoopSnake(window, renderer);
    
    while (!quit){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = 1;
            }
        }
    }
    
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
