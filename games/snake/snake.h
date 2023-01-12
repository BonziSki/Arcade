#ifndef A
#define A


#define HEIGHT 600
#define WIDTH 800

typedef struct Snake
{
    int x;
    int y;
    Snake *next;
}Snake;

typedef struct Fruit
{
    int x;
    int y;
}Fruit;


Snake * createSnake(int snakeSize);
Fruit * createFruit();
void drawSnake(SDL_Window * window, SDL_Renderer * renderer, Snake * snake);
void mainSnake(SDL_Window * window, SDL_Renderer * renderer);
void snakeUpdate(Snake * snake);





#endif