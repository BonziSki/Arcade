#ifndef G
#define G


#define HEIGHT 600
#define WIDTH 800
#define true 1
#define false 0

#include <stdlib.h>
#include <SDL2/SDL.h>




typedef struct Snake
{
    
    int x;
    int y;
    Snake* next;
}Snake;


typedef struct Fruit
{
    int x;
    int y;
}Fruit;


Snake* initializeSnake();
Fruit* initializeFruit();
void mainLoopSnake(SDL_Window* window, SDL_Renderer * renderer);
int updateSnake(Snake * Snake, Fruit * Fruit);







// void insertBeginning(Snake* snake, int x, int y);
// void insertEnd(Snake* snake, int x, int y);
// void deleteBeginning(Snake* snake);
// void deleteEnd(Snake* snake);

#endif