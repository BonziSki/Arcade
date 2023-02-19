#ifndef B
#define B

#define WINNING_SCORE 5

typedef struct Ball{
    int x;
    int y;
    int vertical_direction;
    int horizontal_direction;
    int speed;
    int bounce;
}Ball;

typedef struct Pong_Player{
    int x;
    int y;
    int score;
}Pong_Player;


//Fonctions

Pong_Player * createPongPlayer(int nplayer);
Ball * createPongBall();
void drawPongGame(SDL_Window * window, SDL_Renderer * renderer, Ball * ball, Pong_Player * p1, Pong_Player * p2);
void mainPongLoop(SDL_Window * window, SDL_Renderer * renderer);
int pongUpdate(SDL_Renderer * renderer, Ball * ball, Pong_Player * p1, Pong_Player * p2);




#endif
