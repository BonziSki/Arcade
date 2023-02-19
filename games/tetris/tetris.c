//MAC
// #include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> 
// #include </opt/homebrew/Cellar/sdl_ttf/2.0.11_2/include/SDL/SDL_ttf.h>
//Windows
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "tetris.h"
#include "../../func.h"
#include "../../menu/menu.h"
 

void MainTetrisLoop(SDL_Renderer * renderer){
    SDL_ClearScreen(renderer);
    int score=0;
    DrawControl(renderer);
    int ** permArray = createArray(HEIGTH_TABLE,WIDTH_TABLE);
    int ** miniArray = createArray(3,3);
    int ** tempArray = createArray(3,3);
    int x=WIDTH_TABLE/2;
    int y=0;
    
    Timer * TimeStamp1 = createTimer();
    //number = (rand() % (upper - lower + 1)) + lower
    int color = (rand()%4)+1;
    int choice = (rand()%7)+1;
    updateMiniArray(miniArray,choice,color);
    color = (rand()%4)+1;
    choice = (rand()%7)+1;
    updateMiniArray(tempArray,choice,color);

    int quit=0;
    int update=1;
    while (quit<1)
    {   
        //check GetTickCount()
        // Set to ~60 fps.
        // 1000 ms/ 60 fps = 1/16 s^2/frame
        if (TimeStamp1->initializedTimer==0){
            TimeStamp1->initializedTimer=time(NULL);
        }
        update = updateTetris(permArray,miniArray,&x,&y,&score,renderer,TimeStamp1,&choice,&color);
        if(update==0){
            quit=1;
            
            break;
        }else if (update==2)
        {
            //sortie manuel du joeur
            quit=2;
        };
        cleanArray(tempArray);
        updateMiniArray(tempArray,choice,color);
        DrawGame(renderer, miniArray, permArray,x,y);
        DrawNext(renderer,tempArray);
        DrawScore(renderer,&score);
        SDL_RenderPresent(renderer);
    }
    if (quit==1)
    {
        if(gameOverMenu(renderer, &score) == 1){
            //oui
            printf("\nau revoir !\n");
            freeArray(permArray,20);
            freeArray(tempArray,3);
            freeArray(miniArray,3);
            //score => fichier du high Score si score > High Score
        }else{
        //restart le jeu
            freeArray(permArray,20);
            freeArray(tempArray,3);
            freeArray(miniArray,3);
            MainTetrisLoop(renderer);
            //score => fichier du high Score si score > High Score
        }
    }
}


void DrawScore(SDL_Renderer * renderer,int * score){
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));
    if (SDL_SetRenderDrawColor(renderer, 191, 191, 191, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }
    rect->x=(WIDTH/3)+(CELL_SIZE*WIDTH_TABLE)+10;
    rect->y=(HEIGHT/6)*3;
    rect->w=240;
    rect->h=60;
    SDL_RenderDrawRect(renderer,rect);
    SDL_Color greyWhite = {200, 200, 200};
    //buffer pour sprintf
    char str[12];
    sprintf(str, "%d", *score);
    SDL_WriteTextBuffered(renderer,(rect->x+rect->w/2)-30,rect->y+10,40,40,greyWhite,str);
    free(rect);
}

void DrawNext(SDL_Renderer * renderer,int ** tempArray){
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));
    if (SDL_SetRenderDrawColor(renderer, 191, 191, 191, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }
    rect->x=(WIDTH/3)+(CELL_SIZE*WIDTH_TABLE)+10;
    rect->y=(HEIGHT/6);
    rect->w=240;
    rect->h=180;
    SDL_RenderDrawRect(renderer,rect);
    int first_y=(HEIGHT/6)+60;
    int first_x=(WIDTH/3)+(CELL_SIZE*WIDTH_TABLE)+70;  
    //ici dessin de prochaine pièce
    rect->w = CELL_SIZE;
    rect->h = CELL_SIZE;
    // print tableau mini
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            switch (tempArray[i][j]){
            case 0:
                //case vide
                if (SDL_SetRenderDrawColor(renderer, 191, 191, 191, SDL_ALPHA_OPAQUE) != 0){
                    SDL_ExitWithError("Changement de couleur du rendu");
                }
                    rect->y = first_y+(i*rect->h);
                    rect->x = first_x+(j*rect->w);
                    SDL_RenderDrawRect(renderer,rect);
                break;
            case 1:
            //case pleine coloré 
                if (SDL_SetRenderDrawColor(renderer,77, 219, 255, SDL_ALPHA_OPAQUE) != 0){
                    SDL_ExitWithError("Changement de couleur du rendu");
                }
                    rect->y = first_y+(i*rect->h);
                    rect->x = first_x+(j*rect->w);
                    SDL_RenderFillRect(renderer, rect);
                break;
            case 2:
            //case pleine coloré 
                if (SDL_SetRenderDrawColor(renderer,255, 92, 51, SDL_ALPHA_OPAQUE) != 0){
                    SDL_ExitWithError("Changement de couleur du rendu");
                }
                    rect->y = first_y+(i*rect->h);
                    rect->x = first_x+(j*rect->w);
                    SDL_RenderFillRect(renderer, rect);
                break;
            case 3:
            //case pleine coloré 
                if (SDL_SetRenderDrawColor(renderer,102, 255, 51, SDL_ALPHA_OPAQUE) != 0){
                    SDL_ExitWithError("Changement de couleur du rendu");
                }
                    rect->y = first_y+(i*rect->h);
                    rect->x = first_x+(j*rect->w);
                    SDL_RenderFillRect(renderer, rect);
                break;
            case 4:
            //case pleine coloré 
                if (SDL_SetRenderDrawColor(renderer,204, 51, 153, SDL_ALPHA_OPAQUE) != 0){
                    SDL_ExitWithError("Changement de couleur du rendu");
                }
                    rect->y = first_y+(i*rect->h);
                    rect->x = first_x+(j*rect->w);
                    SDL_RenderFillRect(renderer, rect);
            default:
                break;
            }
        }
    }
}

void DrawControl(SDL_Renderer * renderer){

    SDL_Surface * Surface=malloc(sizeof(SDL_Surface));
    Surface= SDL_LoadBMP("./ressources/textures/choupette_block.bmp");
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer,Surface);
    SDL_FreeSurface(Surface);
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));
    rect->x=60;
    rect->y=100;
    rect->w=120;
    rect->h=120;
    SDL_RenderCopy(renderer,texture,NULL,rect);
    SDL_DestroyTexture(texture);
    free(rect);
}

void DrawGame(SDL_Renderer * renderer,int ** miniArray,int ** permArray,int x, int y){
    int first_x = WIDTH/3;
    int first_y = HEIGHT/6;
    PartialClean(renderer);
    //print tableau permanent 
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));
    rect->w = CELL_SIZE;
    rect->h = CELL_SIZE;
    // print tableau mini
    for (int i = y; i < y+3; i++){
        for (int j = x; j < x+3; j++){
            switch (miniArray[i-y][j-x]){
            case 0:
                break;
            case 1:
            //case pleine coloré 
                if (SDL_SetRenderDrawColor(renderer,77, 219, 255, SDL_ALPHA_OPAQUE) != 0){
                    SDL_ExitWithError("Changement de couleur du rendu");
                }
                    rect->y = first_y+(i*rect->h);
                    rect->x = first_x+(j*rect->w);
                    SDL_RenderFillRect(renderer, rect);
                break;
            case 2:
            //case pleine coloré 
                if (SDL_SetRenderDrawColor(renderer,255, 92, 51, SDL_ALPHA_OPAQUE) != 0){
                    SDL_ExitWithError("Changement de couleur du rendu");
                }
                    rect->y = first_y+(i*rect->h);
                    rect->x = first_x+(j*rect->w);
                    SDL_RenderFillRect(renderer, rect);
                break;
            case 3:
            //case pleine coloré 
                if (SDL_SetRenderDrawColor(renderer,102, 255, 51, SDL_ALPHA_OPAQUE) != 0){
                    SDL_ExitWithError("Changement de couleur du rendu");
                }
                    rect->y = first_y+(i*rect->h);
                    rect->x = first_x+(j*rect->w);
                    SDL_RenderFillRect(renderer, rect);
                break;
            case 4:
            //case pleine coloré 
                if (SDL_SetRenderDrawColor(renderer,204, 51, 153, SDL_ALPHA_OPAQUE) != 0){
                    SDL_ExitWithError("Changement de couleur du rendu");
                }
                    rect->y = first_y+(i*rect->h);
                    rect->x = first_x+(j*rect->w);
                    SDL_RenderFillRect(renderer, rect);
            default:
                break;
            }
        }
    }

if (SDL_SetRenderDrawColor(renderer, 255, 0,0, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }
    for (int i = 0; i < HEIGTH_TABLE; i++){
        for (int j = 0; j < WIDTH_TABLE; j++){
            switch (permArray[i][j]){
            case 0:
            //case vide
                    if (SDL_SetRenderDrawColor(renderer, 191, 191, 191, SDL_ALPHA_OPAQUE) != 0){
                        SDL_ExitWithError("Changement de couleur du rendu");
                    }
                        rect->y = first_y+(i*rect->h);
                        rect->x = first_x+(j*rect->w);
                        SDL_RenderDrawRect(renderer,rect);
                break;
            case 1:
            //case pleine coloré 
                    if (SDL_SetRenderDrawColor(renderer,77, 219, 255, SDL_ALPHA_OPAQUE) != 0){
                        SDL_ExitWithError("Changement de couleur du rendu");
                    }
                        rect->y = first_y+(i*rect->h);
                        rect->x = first_x+(j*rect->w);
                        SDL_RenderFillRect(renderer, rect);
                break;
            case 2:
            //case pleine coloré 
                    if (SDL_SetRenderDrawColor(renderer,255, 92, 51, SDL_ALPHA_OPAQUE) != 0){
                        SDL_ExitWithError("Changement de couleur du rendu");
                    }
                        rect->y = first_y+(i*rect->h);
                        rect->x = first_x+(j*rect->w);
                        SDL_RenderFillRect(renderer, rect);
                break;
            case 3:
            //case pleine coloré 
                    if (SDL_SetRenderDrawColor(renderer,102, 255, 51, SDL_ALPHA_OPAQUE) != 0){
                        SDL_ExitWithError("Changement de couleur du rendu");
                    }
                        rect->y = first_y+(i*rect->h);
                        rect->x = first_x+(j*rect->w);
                        SDL_RenderFillRect(renderer, rect);
                break;
            case 4:
            //case pleine coloré 
                    if (SDL_SetRenderDrawColor(renderer,204, 51, 153, SDL_ALPHA_OPAQUE) != 0){
                        SDL_ExitWithError("Changement de couleur du rendu");
                    }
                        rect->y = first_y+(i*rect->h);
                        rect->x = first_x+(j*rect->w);
                        SDL_RenderFillRect(renderer, rect);
                break;
            default:
                break;
            }
        }
    }
}
int gameOverMenu(SDL_Renderer * renderer, int * score){
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
        rect->x = WIDTH/2-rect->w/2;
        rect->y = 100;

        //rendu du rectangle
        SDL_RenderFillRect(renderer, rect);

        //recentrer les zones   
        SDL_Color greyWhite = {200, 200, 200};
        char * dico[] = {"voulez vous rejouer ?","oui","non"};

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
                                printf("choice : %d\n",choice);
                            }
                            break;

                        case SDLK_UP:
                            if (choice > 0){
                                choice--;
                                printf("choice : %d\n",choice);
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
    return 0;
}