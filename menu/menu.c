#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "../func.h"
#include "../games/pong/pong.h"
#include "menu.h"

void menu(SDL_Window * window, SDL_Renderer * renderer){

    SDL_bool quit = SDL_FALSE;
    int choice = 0;

    while (!quit){
        SDL_Event event;
        drawMenu(window,renderer,choice);
        while (SDL_PollEvent(&event)){
            
            switch (event.type)
            {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                        if (choice<3)
                            choice++;
                        //+1 choix menu
                        break;
                    case SDLK_LEFT:
                            if (choice>0)
                            choice--;
                        //-1 choix menu
                        break;
                    case SDLK_RETURN:
                        switch (choice)
                        {
                            case 0:
                            //pong
                                mainPongLoop(window, renderer);
                                break;
                            case 1:
                                //func(game)
                                break;
                            case 2:
                                //func(game)
                                break;
                            case 3:
                                //func(game)
                                break;
                            default:
                                break;
                        }
                        SDL_RenderPresent(renderer);  
                    break;
                    case SDLK_ESCAPE:
                        if(Escape(window,renderer)==0){
                            quit=SDL_TRUE;
                        };
                        break;
                default:
                    break;
                }
                break;
            case SDL_QUIT:
                quit = SDL_TRUE;
                break;

            default:
                break;
            }
        }
    }
}


void drawMenu(SDL_Window * window, SDL_Renderer * renderer,int choice){
    SDL_Surface * Surface1 = SDL_LoadBMP("./ressources/textures/choupette_block.bmp");
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer,Surface1);
    SDL_FreeSurface(Surface1);
    SDL_ClearScreen(renderer);
    SDL_Rect * textRect = malloc(sizeof(SDL_Rect));
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));
    if (SDL_SetRenderDrawColor(renderer, 255, 0,0, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }
    rect->w = 80;
    rect->h = 80;
    rect->y = 280;

    for (int i = 0; i < 4; i++)
    {
        if (choice==i)
        {
            if (SDL_SetRenderDrawColor(renderer, 0, 0,255, SDL_ALPHA_OPAQUE) != 0){
                SDL_ExitWithError("Changement de couleur du rendu");
            }
        }
        rect->x = 40+ (80 + (rect->w*i*2));
            SDL_RenderFillRect(renderer, rect);
        if (SDL_SetRenderDrawColor(renderer, 255, 0,0, SDL_ALPHA_OPAQUE) != 0){
            SDL_ExitWithError("Changement de couleur du rendu");
        }
    }

    rect->w = rect->w *3;
    rect->h = 80;
    rect->x = WIDTH/2-rect->w/2;
    rect->y = 100;
    SDL_RenderFillRect(renderer, rect);

    textRect->w=80;
    textRect->h=80;
    textRect->x=300;
    textRect->y=400;
    //SDL_RenderFillRect(renderer, textRect);
    SDL_RenderCopy(renderer,texture,NULL,textRect);
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(texture);
    free(textRect);
    free(rect);
}
