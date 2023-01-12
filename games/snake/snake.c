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

Fruit * createFruit(){
    Fruit * pomme = malloc(sizeof(Fruit));
    while (/* condition */)
    {
        /* code */
    }
    

};


// void drawSnake(SDL_Window * window, SDL_Renderer * renderer, Snake * snake){};
// void mainSnake(SDL_Window * window, SDL_Renderer * renderer){};
// void snakeUpdate(Snake * snake){};