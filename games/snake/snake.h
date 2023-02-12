#ifndef G
#define G

#define BEGIN_SNAKE_SIZE 4
#define CASE_SIZE 25
#define MAX_CASE_HEIGHT HEIGHT / CASE_SIZE
#define MAX_CASE_WIDTH WIDTH / CASE_SIZE


typedef struct Fruit
{
    int x;
    int y;
}Fruit;


//--------- SDL ---------
//MAC
#include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> 
#include </opt/homebrew/Cellar/sdl_ttf/2.0.11_2/include/SDL/SDL_ttf.h>
 
//Windows
// #include <SDL2/SDL.h> 
// #include <SDL2/SDL_ttf.h>

//-----------------------

#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#include "snake.h"
#include "../../func.h"



int ** createSnake(int size);
void addSnakeNode(int ** snake, int size, int dir_h, int dir_v);
void createFruit(Fruit * fruit, int ** snake, int size);
void viewAllNodes(int ** snake, int size);
void drawSnake(SDL_Renderer * renderer, int ** snake, int size, Fruit *fruit);
void mainLoopSnake(SDL_Window* window, SDL_Renderer * renderer);
int updateSnake(int ** snake, int size, Fruit * fruit, int * dir_h, int * dir_v);








// void insertBeginning(Snake* snake, int x, int y);
// void insertEnd(Snake* snake, int x, int y);
// void deleteBeginning(Snake* snake);
// void deleteEnd(Snake* snake);

#endif