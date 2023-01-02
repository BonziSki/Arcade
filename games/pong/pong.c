//MAC
#include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> 
#include </opt/homebrew/Cellar/sdl_ttf/2.0.11_2/include/SDL/SDL_ttf.h>
//Windows
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_ttf.h>
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

    temp->horizontal_direction = -1;
    temp->vertical_direction = 1;

    return temp;
}


void resetBall(int hdir, Ball * ball){

    ball->x = WIDTH / 2 - 5;
    ball->y = HEIGHT / 2 - 5;

    ball->horizontal_direction = hdir;
    ball->vertical_direction = hdir;
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

    // //score du joueur 1
    // sprintf(score, "%d", p1->score);
    // SDL_WriteText(renderer, 30, 30, 30, 30, greyWhite, score);

    // //score du joueur 2
    // sprintf(score, "%d", p2->score);
    // SDL_WriteText(renderer, WIDTH - 60, HEIGHT - 60, 30, 30, greyWhite, score);



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

void mainPongLoop(SDL_Window * window, SDL_Renderer * renderer){

    Pong_Player * p1 = createPongPlayer(1);
    Pong_Player * p2 = createPongPlayer(2);
    Ball * ball = createPongBall();

    for (int i = 0; i < 1000; i++){
        pongUpdate(ball, p1, p2);
        drawPongGame(window, renderer, ball, p1, p2);
        SDL_Delay(10);
    }
    
}

void pongUpdate(Ball * ball, Pong_Player * p1, Pong_Player * p2){
    //Update des positions des joueurs
    SDL_Event event;

    while (SDL_PollEvent(&event)){
        if (event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym){
            //touches pour le joueur 1
            case SDLK_z:
                if (p1->y > 10){
                    p1->y = p1->y - 10;
                }else{
                    p1->y = 0;
                }
                break;
            case SDLK_s:
                if(p1->y < HEIGHT - 50){
                    p1->y = p1->y + 10;
                }else{
                    p1->y = HEIGHT - 40;
                }
                break;
            
            //touches pour le joueur 2
            case SDLK_UP:
                if (p2->y > 10){
                    p2->y = p2->y - 10;
                }else{
                    p2->y = 0;
                }
                break;
            case SDLK_DOWN:
                if(p2->y < HEIGHT - 50){
                    p2->y = p2->y + 10;
                }else{
                    p2->y = HEIGHT - 40;
                }
                break;
            
            default:
                break;
            }
        }
    }


    //Update de la position de la balle
    //update X
    ball->x = ball->x + (5 * ball->horizontal_direction);

    if (ball->x > WIDTH - 30){
        //si la balle rebondie sur le joueur 2
        if ((ball->y < p2->y + 40) && (ball->y + 10 > p2->y)){
            ball->horizontal_direction = ball->horizontal_direction * -1;
            ball->x = WIDTH - (ball->x - (WIDTH - 30));
        }else{
            //le joueur 1 marque un point
            p1->score = p1->score + 1;
            resetBall(1, ball);
        }
        
    }else if (ball->x < 30){
        //si la balle rebondie sur le joueur 1
        if ((ball->y < p1->y + 40) && (ball->y + 10 > p1->y)){
            ball->horizontal_direction = ball->horizontal_direction * -1;
            ball->x = ((ball->x - 30) * -1) + 30;
        }else{
            //le joueur 2 marque un point
            p2->score = p2->score + 1;
            resetBall(-1, ball);
        }
    }
    
    

    //update Y
    ball->y = ball->y + (5 * ball->vertical_direction);

    //si la ball dépasse l'écran verticalement 
    if (ball->y > HEIGHT){
        ball->y = HEIGHT - (ball->y - HEIGHT);
        ball->vertical_direction = ball->vertical_direction * -1;
    }else if (ball->y < 0){
        ball->y = ball->y * -1;
        ball->vertical_direction = ball->vertical_direction * -1;
    }
}
