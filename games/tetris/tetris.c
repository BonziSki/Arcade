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
    int ** tempArray = createArray(HEIGTH_TABLE,WIDTH_TABLE);
    int ** permArray = createArray(HEIGTH_TABLE,WIDTH_TABLE);
    int ** miniArray = createArray(3,3);
    int x=WIDTH/2;
    int y=0;
    
    Timer * TimeStamp1 = createTimer();
    //number = (rand() % (upper - lower + 1)) + lower
    updateMiniArray(miniArray,(rand()%(4-1))+1,(rand()%(4-1))+1);

    int quit=0;
    while (!quit)
    {   
        //check GetTickCount()
        // Set to ~60 fps.
        // 1000 ms/ 60 fps = 1/16 s^2/frame
        if (TimeStamp1->initializedTimer==0){
            TimeStamp1->initializedTimer=time(NULL);
        }
        if(updateTetris(permArray,miniArray,&x,&y,&score,renderer,TimeStamp1)==0){
            quit=1;
            break;
        };
        DrawGame(renderer, miniArray, permArray,x,y);
        DrawNext(renderer,miniArray);
        DrawScore(renderer,&score);
        SDL_RenderPresent(renderer);
    }
    SDL_ClearScreen(renderer);
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

void DrawNext(SDL_Renderer * renderer,int ** miniArray){
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));
    if (SDL_SetRenderDrawColor(renderer, 191, 191, 191, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }
    rect->x=(WIDTH/3)+(CELL_SIZE*WIDTH_TABLE)+10;
    rect->y=(HEIGHT/6);
    rect->w=240;
    rect->h=180;
    SDL_RenderDrawRect(renderer,rect);
    int middle_x=rect->x+rect->w/2;
    int middle_y=rect->y+rect->h/2;

    //ici dessin de prochaine pièce
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
    // print tableau temporaire
    for (int i = y; i < y+3; i++){
        for (int j = x; j < x+3; j++){
            switch (miniArray[i][j]){
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