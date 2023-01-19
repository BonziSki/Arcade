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
    char * bmp_string[]= {"./ressources/textures/pong.bmp","./ressources/textures/tron.bmp","./ressources/textures/snake.bmp","./ressources/textures/tetris.bmp"};
    SDL_Surface * Surface[4];
    SDL_Texture * texture[4];
    for (int i = 0; i < 4; i++)
    {
        Surface[i]= SDL_LoadBMP(bmp_string[i]);
        texture[i] = SDL_CreateTextureFromSurface(renderer,Surface[i]);
        SDL_FreeSurface(Surface[i]);
    }
    // SDL_Surface * Surface1 = SDL_LoadBMP("./ressources/textures/choupette_block.bmp");
    SDL_ClearScreen(renderer);
    SDL_Rect * textRect = malloc(sizeof(SDL_Rect));
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));
    if (SDL_SetRenderDrawColor(renderer, 255, 0,0, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }
    rect->w = 80;
    rect->h = 80;
    rect->y = 280;

    textRect->w=80;
    textRect->h=80;
    textRect->y=rect->y;

    for (int i = 0; i < 4; i++)
    {
        if (choice==i)
        {
            if (SDL_SetRenderDrawColor(renderer, 255, 255,255, SDL_ALPHA_OPAQUE) != 0){
                SDL_ExitWithError("Changement de couleur du rendu");
            }
            rect->x=40+ (80 + (rect->w*i*2))-3;
            rect->y-=3;

            rect->w+=6;
            rect->h+=6;
            SDL_RenderFillRect(renderer, rect);
            rect->y+=3;
            rect->w-=6;
            rect->h-=6;
        }
        if (SDL_SetRenderDrawColor(renderer, 255, 0,0, SDL_ALPHA_OPAQUE) != 0){
            SDL_ExitWithError("Changement de couleur du rendu");
        }
        rect->x = 40+ (80 + (rect->w*i*2));
            SDL_RenderFillRect(renderer, rect);
        textRect->x=rect->x;
        SDL_RenderCopy(renderer,texture[i],NULL,textRect);
        

    }

    rect->w = rect->w *3;
    rect->h = 80;
    rect->x = WIDTH/2-rect->w/2;
    rect->y = 100;
    SDL_RenderFillRect(renderer, rect);
    SDL_RenderPresent(renderer);
    for (int i = 0; i < 4; i++)
    {
        SDL_DestroyTexture(texture[i]);
    }
    
    free(textRect);
    free(rect);
}
