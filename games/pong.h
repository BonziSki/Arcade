#ifndef B
#define B

typedef struct Ball{
    int x;
    int y;
    int vertical_direction;
    int horizontal_direction;

}Ball;

typedef struct Pong_Player{
    int x;
    int y;
    /*  0 - gris
        1 - bleu clair
        2 - rouge clair
        3 - jaune clair
        4 - vert clair
        */
    int color;
}Pong_Player;


//Fonctions

Pong_Player * createPongPlayer();
void drawPongGame(Pong_Player * p1, Pong_Player * p2, Ball * ball);






#endif

