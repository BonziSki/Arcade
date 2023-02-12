#ifndef G
#define G

#define CASE_SIZE 25
#define MAX_CASE_HEIGHT HEIGHT / CASE_SIZE
#define MAX_CASE_WIDTH WIDTH / CASE_SIZE

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


Snake * createSnake();
void createFruit(Fruit * fruit,  Snake * snake);

void drawSnake(SDL_Renderer * renderer, Snake * snake, Fruit *fruit);
int updateSnake(Snake * snake,Snake ** snake_pointer, Fruit * fruit, int * dir_h, int * dir_v);

void mainLoopSnake(SDL_Window * window, SDL_Renderer * renderer);
Snake * addSnakeNode(Snake * snake,int dir_h,int dir_v);







// void insertBeginning(Snake* snake, int x, int y);
// void insertEnd(Snake* snake, int x, int y);
// void deleteBeginning(Snake* snake);
// void deleteEnd(Snake* snake);

#endif