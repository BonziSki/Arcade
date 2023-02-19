//MAC
// #include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> 
// #include </opt/homebrew/Cellar/sdl_ttf/2.0.11_2/include/SDL/SDL_ttf.h>
//Windows
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "tron.h"
#include "../../func.h"
#include "../../menu/menu.h"

#define WINNING_SCORE 3
#define CASE_SIZE 10
#define MAP_HEIGHT HEIGHT / CASE_SIZE
#define MAP_WIDTH WIDTH / CASE_SIZE





TronPlayer * createTronPlayer(int pn, int width, int height){
    TronPlayer * temp = malloc(sizeof(TronPlayer));

    if (pn == 1){
        temp->x = (width / 2) - 20;
        temp->y = height / 2;

        temp->dir_h = 1;
        temp->dir_v = 0;

        temp->score = 0;
    }else{
        temp->x = (width / 2) + 20;
        temp->y = height / 2;
        
        temp->dir_h = -1;
        temp->dir_v = 0;

        temp->score = 0;
    }
    
    return temp;
}

int ** createTronMap(int width, int height){
    int ** temp = malloc(sizeof(int *) * height);

    for (int i = 0; i < height; i++){
        temp[i] = malloc(sizeof(int) * width);

        //mise à 0 des cases
        for (int j = 0; j < width; j++){
            temp[i][j] = 0;
        }
    }

    return temp;
}

void viewMap(int ** map){
    printf("\n############## Dessin des trainées du joueur 1 ################\n");
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            if (map[i][j] == 1){
                printf("#");
            }else if (map[i][j] == 2){
                printf("@");
            }else{
                printf("O");
            }
        }
        printf("\n");
    }
}

void drawTron(SDL_Renderer * renderer, int ** map, TronPlayer * p1, TronPlayer * p2){

    //nettoyage de l'écran
    SDL_ClearScreen(renderer);

    
    


    //Rectangle
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));
    


    //Dessin des trainées du joueur 1

    //changement de couleur
    if (SDL_SetRenderDrawColor(renderer, 153, 255, 255, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }

    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            if (map[i][j] == 1){
                rect->x = j * CASE_SIZE;
                rect->y = i * CASE_SIZE;
                rect->w = CASE_SIZE;
                rect->h = CASE_SIZE;

                SDL_RenderFillRect(renderer, rect);
            }
        }
    }
    


    //Dessin des trainées du joueur 2

    //changement de couleur
    if (SDL_SetRenderDrawColor(renderer, 255, 204, 153, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }

    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            if (map[i][j] == 2){
                rect->x = j * CASE_SIZE;
                rect->y = i * CASE_SIZE;
                rect->w = CASE_SIZE;
                rect->h = CASE_SIZE;
            
                SDL_RenderFillRect(renderer, rect);
            }
        }
    }


    //Dessin du joueur 1

    //changement de couleur
    if (SDL_SetRenderDrawColor(renderer, 0, 151, 255, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }

    rect->x = p1->x * CASE_SIZE;
    rect->y = p1->y * CASE_SIZE;
    rect->w = CASE_SIZE;
    rect->h = CASE_SIZE;

    SDL_RenderFillRect(renderer, rect);


    //Dessin du joueur 2

    //changement de couleur
    if (SDL_SetRenderDrawColor(renderer, 255, 158, 0, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }

    rect->x = p2->x * CASE_SIZE;
    rect->y = p2->y * CASE_SIZE;
    rect->w = CASE_SIZE;
    rect->h = CASE_SIZE;

    SDL_RenderFillRect(renderer, rect);



    //affichage de tous les éléments
    SDL_RenderPresent(renderer);
    free(rect);
}



int updateTron(SDL_Renderer * renderer, TronPlayer * p1, TronPlayer * p2, int ** map){

    int lose = 0;

    //Update de la map
    map[p1->y][p1->x] = 1;
    map[(p1->y - p1->dir_v)][(p1->x - p1->dir_h)] = 1;

    map[p2->y][p2->x] = 2;
    map[p2->y - p2->dir_v][p2->x - p2->dir_h] = 2;


    //Detection des touches
    SDL_Event event;

    while (SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            return 2;
        }
        if (event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym){
                //menu pause
                case SDLK_ESCAPE:
                        if(Escape(renderer) == 0){
                            return 2;
                        }
                    break;


                //touches pour le joueur 1
                case SDLK_z:
                    if (p1->dir_v != 1){
                        p1->dir_h = 0;
                        p1->dir_v = -1;
                    }
                    break;

                case SDLK_q:
                    if (p1->dir_h != 1){
                        p1->dir_v = 0;
                        p1->dir_h = -1;
                    }
                    break;

                case SDLK_s:
                    if (p1->dir_v != -1){
                        p1->dir_h = 0;
                        p1->dir_v = 1;
                    }
                    break;

                case SDLK_d:
                    if (p1->dir_h != -1){
                        p1->dir_v = 0;
                        p1->dir_h = 1;
                    }
                    break;
                
                //touches pour le joueur 2
                case SDLK_UP:
                    if (p2->dir_v != 1){
                        p2->dir_h = 0;
                        p2->dir_v = -1;
                    }
                    break;

                case SDLK_DOWN:
                    if (p2->dir_v != -1){
                        p2->dir_h = 0;
                        p2->dir_v = 1;
                    }
                    break;

                case SDLK_LEFT:
                    if (p2->dir_h != 1){
                        p2->dir_v = 0;
                        p2->dir_h = -1;
                    }
                    break;

                case SDLK_RIGHT:
                    if (p2->dir_h != -1){
                        p2->dir_v = 0;
                        p2->dir_h = 1;
                    }
                    break;
                
                default:
                    break;
            }
        }
    }

    
    //Update des positions
    //joueur 1


    if (((p1->x + (2 * p1->dir_h)) >= MAP_WIDTH || (p1->x + (2 * p1->dir_h)) < 0) || ((p1->y + (2 * p1->dir_v)) > MAP_HEIGHT || (p1->y + (2 * p1->dir_v)) < 0) || ((p1->y + (2 * p1->dir_v)) + 1 > MAP_HEIGHT)){
        p2->score = p2->score + 1;
        lose = 1;

    }else if (map[p1->y + (2 * p1->dir_v)][p1->x + (2 * p1->dir_h)] != 0){
        p2->score = p2->score + 1;
        lose = 1;
    }

    p1->x = p1->x + (2 * p1->dir_h);
    p1->y = p1->y + (2 * p1->dir_v);
    


    //joueur 2
    if (((p2->x + (2 * p2->dir_h)) >= MAP_WIDTH || (p2->x + (2 * p2->dir_h)) < 0) || ((p2->y + (2 * p2->dir_v)) > MAP_HEIGHT || (p2->y + (2 * p2->dir_v)) < 0) || ((p2->y + (2 * p2->dir_v)) + 1 > MAP_HEIGHT)){
        p1->score = p1->score + 1;
        lose = 1;

    }else if(map[p2->y + (2 * p2->dir_v)][p2->x + (2 * p2->dir_h)] != 0){
        p1->score = p1->score + 1;
        lose = 1;
    }

    p2->x = p2->x + (2 * p2->dir_h);
    p2->y = p2->y + (2 * p2->dir_v);
    

    //si un joueur à perdu
    if(lose){
        resetTronMap(p1, p2, map, MAP_WIDTH, MAP_HEIGHT);
    }


    //si un joueur atteint le score max
    if (p1->score == WINNING_SCORE){
        return drawWinnerTron(renderer, 1, p1->score, p2->score);
    }else if (p2->score == WINNING_SCORE){
        return drawWinnerTron(renderer, 2, p1->score, p2->score);
    }
    
    return -1;
}

void resetTronMap(TronPlayer * p1, TronPlayer * p2, int ** map, int width, int height){
    //Reset de la position du joueur 1
    p1->x = (width / 2) - 20;
    p1->y = height / 2;

    p1->dir_h = 1;
    p1->dir_v = 0;


    //Reset de la position du joueur 2
    p2->x = (width / 2) + 20;
    p2->y = height / 2;

    p2->dir_h = -1;
    p2->dir_v = 0;


    //Reset de la map
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            map[i][j] = 0;
        }
    }
}

int drawWinnerTron(SDL_Renderer * renderer, int winner, int score_p1, int score_p2){
    //bloquer le jeu jusqu'au relancement de la part du joueur
    int quit = 0;
    int choice = 0;
    SDL_Event event;
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));

    while (!quit){
    //Dessin du menu
        //clear de la fenetre
        SDL_ClearScreen(renderer);

        //changement de couleur du renderer
        if (SDL_SetRenderDrawColor(renderer, 255, 0,0, SDL_ALPHA_OPAQUE) != 0){
            SDL_ExitWithError("Changement de couleur du rendu");
        }

        //
        rect->w = 80;
        rect->h = 60;
        rect->x = 300;

        for (int i = 0; i < 2; i++){
            //on change la couleur du rectangle correspondant au choix du user
            if (choice == i){
                if (SDL_SetRenderDrawColor(renderer, 0, 255,0, SDL_ALPHA_OPAQUE) != 0){
                    SDL_ExitWithError("Changement de couleur du rendu");
                }
            }
            
            //calcul du y du rectangle
            rect->y = 140 + (80 + (rect->h * i * 2));

            //rendu du rectangle
            SDL_RenderFillRect(renderer, rect);

            //reset de la couleur
            if (SDL_SetRenderDrawColor(renderer, 255, 0,0, SDL_ALPHA_OPAQUE) != 0){
                SDL_ExitWithError("Changement de couleur du rendu");
            }
        }

        //deuxieme rectangle
        rect->w = 240;
        rect->h = 80;
        rect->x = WIDTH / 2 - rect->w / 2;
        rect->y = 100;

        //rendu du rectangle
        SDL_RenderFillRect(renderer, rect);

        //recentrer les zones   
        SDL_Color greyWhite = {200, 200, 200};
        char buffer[50];

        sprintf(buffer, "Le vainqueur est le joueur %d", winner);
        char * dico[] = {"voulez vous rejouer ?","oui","non"};
        SDL_WriteTextBuffered(renderer,300,60,180,30,greyWhite,buffer);
        SDL_WriteTextBuffered(renderer,300,120,150,30,greyWhite,dico[0]);
        SDL_WriteTextBuffered(renderer,310,230,40,40,greyWhite,dico[1]);
        SDL_WriteTextBuffered(renderer,310,340,40,40,greyWhite,dico[2]);

        SDL_RenderPresent(renderer);


        //gestion des choix du user
        while (SDL_PollEvent(&event)){
            switch (event.type){

                case SDL_QUIT:
                    return 0;
                    break; 

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym){

                        case SDLK_DOWN:
                            if (choice < 1){
                                choice++;
                                printf("choice : %d",choice);
                            }
                            break;

                        case SDLK_UP:
                            if (choice > 0){
                                choice--;
                                printf("choice : %d",choice);
                            }
                            break;

                        case SDLK_RETURN:
                            return choice;
                            break;
                    }
                    break;
            }
        }
    }
    free(rect);
    return 0;
}





void mainTronLoop(SDL_Window * window, SDL_Renderer * renderer){


    int ** map = NULL;
    map = createTronMap(MAP_WIDTH, MAP_HEIGHT);

    if (map == NULL){
        SDL_ExitWithError("allouage de la mémoire pour la map de tron");
    }

    

    TronPlayer * p1 = NULL;
    p1 = createTronPlayer(1, MAP_WIDTH, MAP_HEIGHT);

    if (p1 == NULL){
        SDL_ExitWithError("allouage de la mémoire pour le joueur 1 de tron");
    }
    
    TronPlayer * p2 = NULL;
    p2 = createTronPlayer(2, MAP_WIDTH, MAP_HEIGHT);

    if (p1 == NULL){
        SDL_ExitWithError("allouage de la mémoire pour le joueur 2 de tron");
    }


    int quitTron = 0;
    int update = 0;

    // testScreen(renderer);
    SDL_Event eventtron;

    while (!quitTron){
        update = updateTron(renderer, p1, p2, map);
        printf("update = %d\n",update);
        if (update==1||update==0){
            //loose
            quitTron=1;
        }else if (update==2){
            //sortie manuel du joeur
            quitTron=2;
        };
        printf("quitTron = %d\n",quitTron);
        if (quitTron==1){
            //reset du score et de la map
            p1->score = 0;
            p2->score = 0;

            resetTronMap(p1, p2, map, MAP_WIDTH, MAP_HEIGHT);
        }
        drawTron(renderer, map, p1, p2);
        
        SDL_Delay(200);
    }
}