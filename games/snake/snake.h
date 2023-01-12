#ifndef G
#define G


// #define HEIGHT 600
// #define WIDTH 800

typedef struct Snake Snake;
struct Snake
{
    int x;
    int y;
    Snake *next;
};

typedef struct Fruit
{
    int x;
    int y;
}Fruit;


Snake * createSnake(int snakeSize);
Fruit * createFruit(Snake * tete);
void drawSnake(SDL_Window * window, SDL_Renderer * renderer, Snake * snake);
void mainSnake(SDL_Window * window, SDL_Renderer * renderer);
void snakeUpdate(Snake * snake);





#endif