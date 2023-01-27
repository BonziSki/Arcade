#ifndef G
#define G

#define WIDTH_TABLE 12
#define HEIGTH_TABLE 22
#define CELL_SIZE 20


void MainTetrisLoop(SDL_Window * window, SDL_Renderer * renderer);
void PartialClean(SDL_Renderer * renderer);
 int ** createTmpTable(int height, int width);
 int ** createPermTable(int height, int width);
void DrawControl(SDL_Renderer * renderer);
void DrawGame(SDL_Renderer * renderer);
void DrawNext(SDL_Renderer * renderer);
void DrawScore(SDL_Renderer * renderer);
void supprLine(int row,int ** permArray,int width)
void updateTetris(int ** tempArray, int ** permArray,int heigth, int width);

#endif