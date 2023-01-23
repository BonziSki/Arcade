#ifndef G
#define G

typedef struct tetrisCell{
    int x;
    int y;
    int size;
    int filled;

}tetrisCell;

typedef struct tetrisView
{
    int width;
    int heigth;
    tetrisCell *** Cell;

}tetrisView;


void MainTetrisLoop(SDL_Window * window, SDL_Renderer * renderer);
void PartialClean(SDL_Renderer * renderer);
 
void DrawControl(SDL_Renderer * renderer);
void DrawGame(SDL_Renderer * renderer);
void DrawNext(SDL_Renderer * renderer);
void DrawScore(SDL_Renderer * renderer);
tetrisCell * CreateCell(int xPos,int yPos);
tetrisView * CreateView();
void tetrisViewSetup(tetrisView * tetrisView);

#endif