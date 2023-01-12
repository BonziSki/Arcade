//MAC
// #include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> 
// #include </opt/homebrew/Cellar/sdl_ttf/2.0.11_2/include/SDL/SDL_ttf.h>
 
//Windows
#include <SDL2/SDL.h> 
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "snake.h"
#include <SDL2/SDL.h>
#include <time.h>

//SNAKE CREATION
Snake * createSnake(int snakeSize){
    Snake * tete = malloc(sizeof(Snake));
    if (snakeSize>0)
    {
        tete->x = 20 + (snakeSize - 2);
        tete->y = 15;
        tete->next = createSnake(snakeSize-1);
    
        return tete;
    }else{
        return NULL;
    }
};

//RANDOM FRUIT POSITION
Fruit * createFruit(Snake * tete){
    Fruit * pomme = malloc(sizeof(Fruit));
    
    while (tete = tete->next)
    {
        pomme->x = rand()%(40);
        pomme->y = rands()%(30);
    }

    return pomme;
};

void drawSnake(SDL_Window * window, SDL_Renderer * renderer, Snake * snake){
    //nettoyage de l'écran
    SDL_ClearScreen(renderer);

    //changement de couleur
    if (SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }

    //Dessin du terrain
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));

    
    //Dessin du snake
    rect->x = snake->x;
    rect->y = snake->y;
    rect->w = 10;
    rect->h = 10;

    if (SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }

    SDL_RenderFillRect(renderer, rect);

    

    //affichage de tous les éléments
    SDL_RenderPresent(renderer);
};





// void mainSnake(SDL_Window * window, SDL_Renderer * renderer){};
// void snakeUpdate(Snake * snake){};