#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

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
    clean(window);
    //dessin
    //...drawmenu
    
}
