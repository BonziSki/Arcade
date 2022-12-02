#include </opt/homebrew/Cellar/sdl2/2.26.0/include/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "pong.h"
#include "func.h"


Pong_Player * createPongPlayer(Pong_Player * player, int nplayer, int color){
    Pong_Player * temp = malloc(sizeof(Pong_Player));

    if (nplayer == 1){
        temp->x = 20;
        temp->y = (HEIGHT / 2) - 20;
    }else if (nplayer == 2){
        temp->x = HEIGHT - 20;
        temp->y = (HEIGHT / 2) - 20;
    }else{
        SDL_ExitWithError("Arguments non valides");
        return NULL;
    }

    temp->color = color;

    return temp;    
};


void drawPongGame(Pong_Player * p1, Pong_Player * p2, Ball * ball);
