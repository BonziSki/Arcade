#ifndef G
#define G

#define WIDTH_TABLE 10
#define HEIGTH_TABLE 20
#define CELL_SIZE 20

typedef struct Timer
{
    int initializedTimer;
}Timer;


Timer * createTimer();
void MainTetrisLoop(SDL_Window * window, SDL_Renderer * renderer);
void PartialClean(SDL_Renderer * renderer);
 int ** createTmpTable(int height, int width);
 int ** createPermTable(int height, int width);
void DrawControl(SDL_Renderer * renderer);
void DrawGame(SDL_Renderer * renderer,int ** tempArray,int ** permArray);
void DrawNext(SDL_Renderer * renderer,int choice, int color);
void DrawScore(SDL_Renderer * renderer,int score);
void supprLine(int row,int ** permArray,int width, int heigth);
int updateTetris(int ** tempArray, int ** permArray,int heigth, int width,int * score, SDL_Renderer * renderer,Timer * timestamp);
void copyArrayInto(int ** tempArray,int ** permArray,int heigth, int width);
void SpawnTetroid(int ** tempArray,int heigth,int width,int color, int choice);

#endif