#ifndef G
#define G


#define HEIGHT 600
#define WIDTH 800
#define true 1
#define false 0

#include <stdlib.h>
#include <SDL2/SDL.h>

typedef struct {
    SDL_Rect body;
    struct Node* next;
} Node;

typedef struct Snake Snake;
struct Snake
{
    
    int x;
    int y;
    Node *head, *tail;
};

Snake* initializeSnake();
void insertBeginning(Snake* snake, int x, int y);
void insertEnd(Snake* snake, int x, int y);
void deleteBeginning(Snake* snake);
void deleteEnd(Snake* snake);
//void mainSnake();

#endif