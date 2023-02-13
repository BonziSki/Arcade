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
 


int ** createTmpTable(int height, int width){
    int ** tempArray = malloc(sizeof(int *) * height);
    for (int i = 0; i < height; i++)
    {
        tempArray[i]=malloc(sizeof(int)*width);
        for (int j = 0; j < width; j++)
        {
            tempArray[i][j]=0;
        }
        
    }
    
    return tempArray;
}
int ** createPermTable(int height, int width){
    int ** permArray = malloc(sizeof(int *) * height);
    for (int i = 0; i < height; i++)
    {
        permArray[i]=malloc(sizeof(int)*width);
        for (int j = 0; j < width; j++)
        {
            permArray[i][j]=0;
        }
    }
    
    return permArray;
}


Timer * createTimer(int x, int y){
    Timer * temp = malloc(sizeof(Timer));
    temp->initializedTimer=0;
    return temp;
}

int updateTetris(int ** tempArray, int ** permArray,int heigth, int width, int * score, SDL_Renderer * renderer,Timer * timestamp){  
    SDL_Event event;

    int coll_flag=0;
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
            //quitter le programme
            return 0;
        }
        if (event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym){
            case SDLK_RIGHT:
            for (int i = 0; i < heigth; i++){
                    //check coll temp array
                    if (tempArray[i][width-1]!=0){
                        coll_flag=1;
                    }
                    //check coll permarray si pas a droite max déja
                    if (coll_flag!=1){
                        for (int i = 0; i < heigth; i++){
                            for (int j = width-1; j > 0; j--){
                                if (tempArray[i][j]!=0){
                                    if (permArray[i][j+1]){
                                        coll_flag=1;
                                    }
                                }
                            }
                        }
                    }   
                }
                if (coll_flag!=1){
                    for (int i = 0; i < heigth; i++){
                        for (int j = width-1; j>0; j--){
                            tempArray[i][j]=tempArray[i][j-1];
                            tempArray[i][j-1]=0;
                        }
                    }
                }
                        //ICI CHECK COLLISION AVEC LA DROITE
                break;
            case SDLK_LEFT:
                for (int i = 0; i < heigth; i++){
                    //check coll temp array
                    if (tempArray[i][0]!=0){
                        coll_flag=1;
                    }
                    //check coll permarray si pas a gauche max déja
                    if (coll_flag!=1){
                        for (int i = 0; i < heigth; i++){
                            for (int j = 0; j < width-1; j++){
                                if (tempArray[i][j]!=0){
                                    if (permArray[i][j-1]){
                                        coll_flag=1;
                                    }
                                }
                            }
                        }
                    }       
                }
                if (coll_flag!=1){
                    for (int i = 0; i < heigth; i++){
                        for (int j = 0; j < width-1; j++){
                            tempArray[i][j]=tempArray[i][j+1];
                            tempArray[i][j+1]=0;
                        }
                    }
                }
                        //ICI CHECK COLLISION AVEC LA GAUCHE
                break;
            case SDLK_DOWN:
                    //directement jump a l'instruction de descente et skip le timestamp
                goto descente;
                break;
            case SDLK_UP:
                        //rotation avec la flèche du haut
                        getTablInTabl(tempArray,heigth,width);
                        break;
            case SDLK_ESCAPE:
                        if(Escape(renderer)==0){
                            return 0;
                        };
                        break;
            default:
                break;
            }
        }
    }
    //si 1 seconde écoulé descendre 
    // a regarde GetTickCount()
    if (time(NULL)>timestamp->initializedTimer){
        descente:
        for (int i = heigth-1; i > 0; i--){
            for (int j = 0; j < width; j++)
            {
                tempArray[i][j]=tempArray[i-1][j];
                tempArray[i-1][j]=0;
            } 
        }
        timestamp->initializedTimer=0;
    }
    //collision avec juste sol
    for (int i = 0; i < width; i++){
        if (tempArray[heigth-1][i]!=0){
            copyArrayInto(tempArray,permArray,heigth,width);
            SpawnTetroid(tempArray,heigth,width,(rand()%(4-1))+1,(rand()%(7-1))+1);
        }
    }
    //collsiion avec permArray
    for (int i = heigth-1; i > 0; i--){
        for (int j = 0; j < width; j++){
            if (tempArray[i][j]!=0){
                if (permArray[i+1][j]!=0){
                    copyArrayInto(tempArray,permArray,heigth,width);
                    SpawnTetroid(tempArray,heigth,width,(rand()%(4-1))+1,(rand()%(7-1))+1);
                }
            } 
        } 
    }
    //check si ligne complète
    int lineFlag=0;
    for (int i = heigth-1; i > 0; i--){
        for (int j = 0; j < width-1; j++){
            if (permArray[i][j]!=0){
                lineFlag=1;
            }else {
                lineFlag=0;
            }
        }
        //BUG de check sur la droite du tableau
        if (lineFlag==1){
            lineFlag=0;
            score+=100;
            printf("Ligne complet\nscore=%d\n",score);
            supprLine(i,permArray,width,heigth);
        }
    }
    return 1;
}

void SpawnTetroid(int ** tempArray,int heigth,int width,int color, int choice){
    if (tempArray[0][width/2]!=0){
        //loose screen
    }
    
    switch (choice){
    case 1:
        //line shape
        tempArray[0][width/2]=color;
        tempArray[0][width/2-1]=color;
        tempArray[0][width/2+1]=color;
        tempArray[0][width/2+2]=color;
        break;
     case 2:
        //L shape
        tempArray[1][width/2]=color;
        tempArray[1][width/2-1]=color;
        tempArray[1][width/2+1]=color;
        tempArray[0][width/2+1]=color;
        break;
    case 3:
        //reverse L shape
        tempArray[1][width/2]=color;
        tempArray[0][width/2-1]=color;
        tempArray[1][width/2+1]=color;
        tempArray[1][width/2-1]=color;
        break;
    case 4:
        //square shape
        tempArray[1][width/2]=color;
        tempArray[1][width/2+1]=color;
        tempArray[0][width/2]=color;
        tempArray[0][width/2+1]=color;
        break;
    case 5:
        //S shape
        tempArray[0][width/2]=color;
        tempArray[0][width/2+1]=color;
        tempArray[1][width/2]=color;
        tempArray[1][width/2-1]=color;
        break;
     case 6:
        //Z (or reverse S) shape
        tempArray[0][width/2]=color;
        tempArray[0][width/2-1]=color;
        tempArray[1][width/2]=color;
        tempArray[1][width/2+1]=color;
        break;
    case 7:
        // T shape
        tempArray[0][width/2]=color;
        tempArray[1][width/2]=color;
        tempArray[1][width/2+1]=color;
        tempArray[1][width/2+-1]=color;
        break;                           
    default:
        break;
    }
}

void supprLine(int row,int ** permArray,int width, int heigth){
    for (int i = 0; i < width; i++){
        permArray[row][i]=0;
    }
    // for (int i = row; i > 0; i--){
    //    for (int j = 0; j < width; j++){
    //     permArray[i][j]=permArray[i-1][j];
    //     permArray[i-1][j]=0;
    //    }
    // }
}
void copyArrayInto(int ** tempArray,int ** permArray,int heigth, int width){
    for (int i = 0; i < heigth; i++){
        for (int j = 0; j < width; j++){
            if (tempArray[i][j]!=0){
                permArray[i][j]=tempArray[i][j];
                tempArray[i][j]=0;
            }  
        }
    }
}


//clean tous sauf les controles que l'ont ne redessine pas
void PartialClean(SDL_Renderer * renderer){

    if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE)){
        SDL_ExitWithError("Impossible de changer de couleur");
    }

    SDL_Rect  FillBlack = {
        .x = WIDTH/4,
        .y = 0,
        .h = HEIGHT,
        .w = WIDTH
    };


    if (SDL_RenderFillRect(renderer, &FillBlack)){
        SDL_ExitWithError("Impossible de clear l'écran");
    }
}