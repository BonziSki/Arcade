#ifndef F
#define F


typedef struct TronPlayer{
    int x;
    int y;
    int dir_h;
    int dir_v;
    int score;
}TronPlayer;


//Fonctions

TronPlayer * createTronPlayer(int pn, int width, int height);
int ** createTronMap(int width, int height);

void drawTron(SDL_Renderer * renderer, int ** map, TronPlayer * p1, TronPlayer * p2);


int updateTron(TronPlayer * p1, TronPlayer * p2, int ** map);

int updateTronScore(TronPlayer * p1, TronPlayer * p2, int looser);
void drawWinner(SDL_Renderer * renderer, int winner, int score_p1, int score_p2);
void mainTronLoop(SDL_Window * window, SDL_Renderer * renderer);



#endif
