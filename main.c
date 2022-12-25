//#define SDL_MAIN_HANDLED
//MAC
#include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> 
#include </opt/homebrew/Cellar/sdl_ttf/2.0.11_2/include/SDL/SDL_ttf.h>
//Windows
//#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "menu/menu.h"
#include "func.h"
#include "games/pong/pong.h"


/*
commande de compilation :
MAC :   gcc main.c -o prog $(sdl2-config --cflags --libs)
        gcc main.c func.c ./menu/menu.c -o prog $(sdl2-config --cflags --libs) -lSDL_ttf
WINDOWS : gcc main.c -o prog.exe -lmingw32 -lSDL2main -lSDL2 
WINDOWS sans terminal : gcc main.c -o prog.exe -I include -L lib -lmingw32 -lSDL2main -lSDL2 -mwindows
*/


int main(int argc, char **argv){

    //SDL_PrintVersion();

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


    //menu(window,renderer);  
    // SDL_Event event;
    // int quit = 0;
    // while (!quit){
        //preMenu(window, renderer);
//----------------------------

    //TTF_Init();

    // Load our font file and set the font size
    TTF_Font * ourFont = TTF_OpenFont("./ressources/font/ARCADEPI.TTF",20);
    // Confirm that it was loaded

    // Pixels from our text

    SDL_Color White = {255, 255, 255};
    SDL_Surface* surfaceText = TTF_RenderText_Solid(ourFont,"TEST",White);

    // Setup the texture
    SDL_Texture* textureText = SDL_CreateTextureFromSurface(renderer,surfaceText);

    // Free the surface
    // We are done with it after we have uploaded to
    // the texture
    SDL_FreeSurface(surfaceText); 

    // Create a rectangle to draw on
    SDL_Rect rectangle;
    rectangle.x = 10;
    rectangle.y = 10;
    rectangle.w = 400;
    rectangle.h = 100;


    // (2) Handle Updates
    
    // (3) Clear and Draw the Screen
    // Gives us a clear "canvas"
    SDL_SetRenderDrawColor(renderer,255,0,0,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Render our text on a rectangle
    SDL_RenderCopy(renderer,textureText,NULL,&rectangle);

    // Finally show what we've drawn
    SDL_RenderPresent(renderer);

    SDL_Delay(2000);

    // Destroy our textured text
    SDL_DestroyTexture(textureText);

    // We destroy our window. We are passing in the pointer
    // that points to the memory allocated by the 
    // 'SDL_CreateWindow' function. Remember, this is
    // a 'C-style' API, we don't have destructors.
    
    // Close our font subsystem
    TTF_CloseFont(ourFont);

//-------------------------------




    //     while (SDL_PollEvent(&event)){
    //         if (event.type == SDL_QUIT){
    //             quit = 1;
    //         }
    //     }
    
  /*
  var gameplayed = 0;
  0=menu
  1=snake
  ...
  */
    //TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
