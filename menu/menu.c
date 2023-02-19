//MAC
// #include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h>
// #include </opt/homebrew/Cellar/sdl_ttf/2.0.11_2/include/SDL/SDL_ttf.h>
//Windows
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "../func.h"
#include "../games/pong/pong.h"
#include "../games/snake/snake.h"
#include "../games/tetris/tetris.h"
#include "../games/tron/tron.h"
#include "menu.h"

void preMenu(SDL_Window * window, SDL_Renderer * renderer){
    TTF_Init();
    TTF_Font * ArcadeFont = TTF_OpenFont("ressources/font/ARCADEPI.ttf", 10);

    // this is the color in rgb format,
    // maxing out all would give you the color white,
    // and it will be your text's color
    SDL_Color White = {255, 255, 255};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(ArcadeFont, "press any key", White);

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);


    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate 
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = 100; // controls the width of the rect
    Message_rect.h = 100; // controls the height of the rect

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);

    TTF_CloseFont(ArcadeFont);
}

void menu(SDL_Window * window, SDL_Renderer * renderer){
    SDL_bool quit = SDL_FALSE;
    int choice = 0;
    while (!quit){
        drawMenu(window,renderer,choice);
        SDL_Event event;
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
                                //TRON
                                mainTronLoop(window,renderer);
                                break;
                            case 2:
                                //SNAKE
                                mainLoopSnake(window,renderer);
                                break;
                            case 3:
                                MainTetrisLoop(renderer);
                                break;
                            default:
                                break;
                        }
                        SDL_RenderPresent(renderer);  
                    break;
                    case SDLK_ESCAPE:
                        if(Escape(renderer)==0){
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
