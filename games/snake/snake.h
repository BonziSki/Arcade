#ifndef G
#define G

// #include <SDL2/SDL.h> 

#define HEIGHT 600
#define WIDTH 800
#define true 1
#define false 0


typedef struct Snake Snake;
struct Snake
{
    int x;
    int y;
    Snake * next;
};


typedef struct Fruit
{
    int x;
    int y;
}Fruit;


Snake* initializeSnake();
void initializeFruit(Fruit * fruit);
void drawSnake(Snake * snake, Fruit *fruit, SDL_Renderer * renderer);
void mainLoopSnake(SDL_Window * window, SDL_Renderer * renderer);
//int updateSnake(Snake * Snake, Fruit * Fruit);s








// void insertBeginning(Snake* snake, int x, int y);
// void insertEnd(Snake* snake, int x, int y);
// void deleteBeginning(Snake* snake);
// void deleteEnd(Snake* snake);

#endif