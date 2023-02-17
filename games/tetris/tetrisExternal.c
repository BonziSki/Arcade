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
 


int ** createArray(int height, int width){
    int ** Array = malloc(sizeof(int *) * height);
    for (int i = 0; i < height; i++){
        Array[i]=malloc(sizeof(int)*width);
        for (int j = 0; j < width; j++){
            Array[i][j]=0;
        } 
    }
    return Array;
}


Timer * createTimer(){
    Timer * temp = malloc(sizeof(Timer));
    temp->initializedTimer=0;
    return temp;
}

int updateTetris(int ** permArray, int ** miniArray,int * x,int * y,int * score, SDL_Renderer * renderer,Timer * TIMESTAMP){  
    SDL_Event event;
    
    int coll_flag=0;
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
            //quitter le programme
            return 0;
        }
        if (event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym){
            case SDLK_LEFT:
            //si déja tous a doite, rien faire
            for (int i = 0; i < 3; i++)
            {
                if (miniArray[i][0]!=0){
                    if (*x==-1){
                        coll_flag=1;
                    }else if (*x==0){
                        coll_flag=1;
                    }
                }
            }
            //check collision permArray
            if (coll_flag!=1){
                for (int i = 0; i < 3; i++)
                {
                    if (miniArray[i][0]!=0)
                    {
                        for (int j = 0; j < 3; j++){
                            if (permArray[i+*y][j+*x]!=0){
                                coll_flag=1;
                            }
                        } 
                    }else{
                        for (int j = 0; j < 3; j++){
                            if (permArray[i+*y][j+*x-1]!=0){
                                coll_flag=1;
                            }
                        } 
                    }
                }
                if (coll_flag!=1){
                    *x-=1;
                }
            }
            //ICI CHECK COLLISION AVEC LA DROITE
                break;
            case SDLK_RIGHT:
            //si déja tous a gauche, rien faire
            if (*x==WIDTH_TABLE-1){
                coll_flag=1;
            }
            //check collision permArray
            if (coll_flag!=1){
                for (int i = 0; i < 3; i++)
                {
                    if (miniArray[i][2]!=0)
                    {
                        for (int j = 0; j < 3; j++){
                            if (permArray[i+*y][j+*x]!=0){
                                coll_flag=1;
                            }
                        } 
                    }else{
                        for (int j = 0; j < 3; j++){
                            if (permArray[i+*y][j+*x+1]!=0){
                                coll_flag=1;
                            }
                        }
                    }
                }
                if (coll_flag!=1){
                    *x+=1;
                }
            }
            //ICI CHECK COLLISION AVEC LA GAUCHE
                break;
            case SDLK_DOWN:
                    //directement jump a l'instruction de descente et skip le timestamp
                goto descente;
                break;
            case SDLK_UP:
                        // //rotation avec la flèche du haut
                        rotation(miniArray);
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
    if (time(NULL)>TIMESTAMP->initializedTimer){
        descente:
        TIMESTAMP->initializedTimer=0;
        *y+=1;
    }
    //collsiion avec permArray
    //BUG
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (miniArray[i][j]!=0){
                if (permArray[i+*y][j+*x]!=0){
                printf("COL \n");
                LockArrayInto(miniArray,permArray,*x,*y-1);
                cleanArray(miniArray);
                updateMiniArray(miniArray,(rand()%(7))+1,(rand()%(4))+1);
                *x=WIDTH_TABLE/2;
                *y=0;
                
                }
            }
        }  
    }
    //collision avec juste sol
    //BUG
    for (int i = 2; i > -1; i--){
        if (miniArray[2][i]!=0){
            if(*y==HEIGTH_TABLE-1){
                printf("SOL 1 \n");
                LockArrayInto(miniArray,permArray,*x,*y);
                cleanArray(miniArray);
                updateMiniArray(miniArray,(rand()%(7))+1,(rand()%(4))+1);
                *x=WIDTH_TABLE/2;
                *y=0;
            }
        }
        else{
            if(*y==HEIGTH_TABLE-2){
                printf("SOL 2 \n");
                LockArrayInto(miniArray,permArray,*x,*y);
                cleanArray(miniArray);
                updateMiniArray(miniArray,(rand()%(7))+1,(rand()%(4))+1);
                *x=WIDTH_TABLE/2;
                *y=0;
            }
        }
    }
    

    //check si ligne complète
    //bug
    int lineFlag=1;
    for (int i = HEIGTH_TABLE-1; i > 0; i--){
        for (int j = 0; j < WIDTH_TABLE; j++){
            if (permArray[i][j]==0){
                lineFlag=0;
            }
        }
        if (lineFlag==1){
            lineFlag=0;
            *score+=100;
            printf("Ligne complet\nscore=%d\n",*score);
            supprLine(i,permArray);
        }
    }
    
    return 1;
}

void updateMiniArray(int ** miniArray, int choice,int color){
    // a faire collision
    switch (choice){
    case 1:
        //line shape
        miniArray[1][0]=color;
        miniArray[1][1]=color;
        miniArray[1][2]=color;
        break;
     case 2:
        //L shape
        miniArray[0][2]=color;
        miniArray[1][2]=color;
        miniArray[1][1]=color;
        miniArray[1][0]=color;
        break;
    case 3:
        //reverse L shape
        miniArray[0][0]=color;
        miniArray[1][2]=color;
        miniArray[1][1]=color;
        miniArray[1][0]=color;
        
        break;
    case 4:
        //square shape
        miniArray[0][0]=color;
        miniArray[0][1]=color;
        miniArray[1][0]=color;
        miniArray[1][1]=color;
        break;
    case 5:
        //S shape
        miniArray[0][2]=color;
        miniArray[0][1]=color;
        miniArray[1][0]=color;
        miniArray[1][1]=color;
        break;
     case 6:
        //Z (or reverse S) shape
        miniArray[0][0]=color;
        miniArray[0][1]=color;
        miniArray[1][2]=color;
        miniArray[1][1]=color;
        break;
    case 7:
        // T shape
        miniArray[0][1]=color;
        miniArray[1][0]=color;
        miniArray[1][2]=color;
        miniArray[1][1]=color;
        break;                    
    default:
        break;
    }
}

void cleanArray(int ** miniArray){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
                miniArray[i][j]=0;
        }
    }
}

void supprLine(int row,int ** permArray){
    for (int i = 0; i < WIDTH_TABLE; i++){
        permArray[row][i]=0;
    }
    for (int i = row; i > 0; i--)
    {
        for (int j = 0; j < WIDTH_TABLE; j++)
        {
            permArray[i][j]=permArray[i-1][j];
        }
        
    }
    
}
void copyArrayInto(int ** sourceArray,int ** destArray,int x,int y){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
                destArray[i+y][j+x]=sourceArray[i][j];
        }
    }
}
void LockArrayInto(int ** sourceArray,int ** destArray,int x,int y){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (sourceArray[i][j]!=0)
            {
                destArray[i+y][j+x]=sourceArray[i][j];
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