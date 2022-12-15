//#include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> //MAC
#include <SDL2/SDL.h>   //Windows
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
    temp->score = 0;

    return temp;    
};


void drawPongGame(SDL_Window * window, SDL_Renderer * renderer, Pong_Player * p1, Pong_Player * p2, Ball * ball){

    if (SDL_SetRendererDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE))
    {
        /* code */
    }
    

    //Dessin du terrain

    //Dessin du score

    //Dessin des joueurs

    //Dessin de la balle
};
