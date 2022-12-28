//#include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> //MAC
#include <SDL2/SDL.h>   //Windows
#include <stdio.h>
#include <stdlib.h>

#include "pong.h"
#include "../../func.h"


Pong_Player * createPongPlayer(int nplayer){
    Pong_Player * temp = malloc(sizeof(Pong_Player));

    if (nplayer == 1){
        temp->x = 20;
        temp->y = (HEIGHT / 2) - 20;
    }else if (nplayer == 2){
        temp->x = WIDTH - 20;
        temp->y = (HEIGHT / 2) - 20;
    }else{
        SDL_ExitWithError("Arguments non valides");
        return NULL;
    }
    temp->score = 0;

    return temp;    
};

Ball * createPongBall(){
    Ball * temp = malloc(sizeof(Ball));

    temp->x = WIDTH / 2 - 5;
    temp->y = HEIGHT / 2 - 5;

    temp->horizontal_direction = 1;
    temp->vertical_direction = 1;

    return temp;
}


void drawPongGame(SDL_Window * window, SDL_Renderer * renderer, Ball * ball, Pong_Player * p1, Pong_Player * p2){

    //nettoyage de l'écran
    SDL_ClearScreen(renderer);

    //changement de couleur
    if (SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }

    //Dessin du terrain
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));

    //dessin de la ligne du milieu
    for (int i = 0; i < HEIGHT; i++){
        rect->x = WIDTH / 2 - 3;
        rect->y = i * 40;
        rect->w = 6;
        rect->h = 20;
    
        SDL_RenderFillRect(renderer, rect);
    }
    
    //Dessin du score
    SDL_Color greyWhite = {200, 200, 200};
    char * score[2];

    //score du joueur 1
    sprintf(score, "%d", p1->score);
    SDL_WriteText(renderer, 30, 30, 30, 30, greyWhite, score);

    //score du joueur 2
    sprintf(score, "%d", p2->score);
    SDL_WriteText(renderer, WIDTH - 60, HEIGHT - 60, 30, 30, greyWhite, score);



    //Dessin des joueurs
    //J1
    rect->x = p1->x;
    rect->y = p1->y;
    rect->w = 10;
    rect->h = 40;

    if (SDL_SetRenderDrawColor(renderer, 255, 200, 200, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }

    SDL_RenderFillRect(renderer, rect);


    //J2
    rect->x = p2->x;
    rect->y = p2->y;
    rect->w = 10;
    rect->h = 40;

    if (SDL_SetRenderDrawColor(renderer, 200, 200, 255, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }

    SDL_RenderFillRect(renderer, rect);


    //Dessin de la balle
    rect->x = ball->x;
    rect->y = ball->y;
    rect->w = 10;
    rect->h = 10;

    if (SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }

    SDL_RenderFillRect(renderer, rect);

    

    //affichage de tous les éléments
    SDL_RenderPresent(renderer);
};
