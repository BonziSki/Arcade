//MAC
// #include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> 
// #include </opt/homebrew/Cellar/sdl_ttf/2.0.11_2/include/SDL/SDL_ttf.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "../func.h"
#include "../games/pong/pong.h"
#include "menu.h"

int Escape(SDL_Renderer * renderer){
    SDL_bool quit = SDL_FALSE;
    int choice = 0;

    while (!quit){
        SDL_Event event;
        DrawEscape(renderer,choice);
        while (SDL_PollEvent(&event)){
        
            switch (event.type){
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym){
                        case SDLK_DOWN:
                            if (choice < 1)
                            choice++;
                            printf("choice : %d",choice);
                            break;

                        case SDLK_UP:
                        //0 == oui
                            if (choice > 0)
                            choice--;
                            printf("choice : %d",choice);
                            break;

                        case SDLK_RETURN:
                            return choice;
                            break;
                    }
                    break; 

                case SDL_QUIT:
                    quit = SDL_TRUE;
                    break; 
            }
        }
    }
    return 0;
}



void DrawEscape(SDL_Renderer * renderer, int choice){
    SDL_ClearScreen(renderer);
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));
    if (SDL_SetRenderDrawColor(renderer, 255, 0,0, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }



    rect->w = 80;
    rect->h = 60;
    rect->x = 300;

    for (int i = 0; i < 2; i++){
        if (choice==i)
        {
            if (SDL_SetRenderDrawColor(renderer, 0, 255,0, SDL_ALPHA_OPAQUE) != 0){
                SDL_ExitWithError("Changement de couleur du rendu");
            }
        }
        rect->y = 140 + (80 + (rect->h*i*2));
            SDL_RenderFillRect(renderer, rect);
        if (SDL_SetRenderDrawColor(renderer, 255, 0,0, SDL_ALPHA_OPAQUE) != 0){
            SDL_ExitWithError("Changement de couleur du rendu");
        }
    }
    rect->w = 240;
    rect->h = 80;
    rect->x = WIDTH/2-rect->w/2;
    rect->y = 100;
    SDL_RenderFillRect(renderer, rect);

//recentrer les zones
    SDL_Color greyWhite = {200, 200, 200};
    char * dico[] = {"voulez vous quitter?","oui","non"};

        SDL_WriteTextBuffered(renderer,300,120,150,30,greyWhite,dico[0]);
        SDL_WriteTextBuffered(renderer,310,230,40,40,greyWhite,dico[1]);
        SDL_WriteTextBuffered(renderer,310,340,40,40,greyWhite,dico[2]);

    SDL_RenderPresent(renderer);
    free(rect);
}