//MAC
#include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h>
#include </opt/homebrew/Cellar/sdl_ttf/2.0.11_2/include/SDL/SDL_ttf.h>
//Windows
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
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
    int choice = 1;
    while (!quit){
        drawMenu(window,renderer,0);
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            switch (event.type)
            {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                        if (choice==4)
                        {}else{
                            choice++;
                        }

                        //+1 choix menu
                        break;
                    case SDLK_LEFT:
                        if (choice==0)
                        {}else{
                            choice--;
                        }
                        //-1 choix menu
                        break;
                    case SDLK_KP_ENTER:
                        switch (choice)
                        {
                            case 1:
                                //func(game)
                                break;
                            case 2:
                                //func(game)
                                break;
                            case 3:
                                //func(game)
                                break;
                            case 4:
                                //func(game)
                                break;
                            default:
                                break;
                        }
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
    //clean(window);
    //dessin
    //...drawmenu
    
}
