//MAC
// #include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> 
// #include </opt/homebrew/Cellar/sdl_ttf/2.0.11_2/include/SDL/SDL_ttf.h>
//Windows
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

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


void updateTetris(int ** tempArray, int ** permArray,int heigth, int width, int * score){  
    int flag =0;
    int lineFlag= 1;
    //Check collision
    for (int i = 0; i < heigth; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (tempArray[i][j]!=0)
            {
                if (permArray[i+1][j]!=0){
                    //trigger flag
                    flag=1;
                }
            }
            // if (flag==1)
            // {
            //     break;
            // }
        }
        // if (flag==1)
        // {
        //     break;
        // }   
    }
    // //copie tableau temp dans perm moins cellule vide
    if (flag==1)
    {
        for (int i = 0; i < heigth; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (tempArray[i][j]!=0)
                {
                    permArray[i][j]=tempArray[i][j];
                }  
            }
        }
    //     //check si ligne complète est vrai
        for (int i = 0; i < heigth; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    if (permArray[i][j]==0)
                    {
                        lineFlag=0;
                    }else{
                        //break;
                        }
                }
                if (lineFlag==1)
                {
                    supprLine(i,permArray,width,heigth);
                    *score+=100;
                }
            }
    //     //sinon descendre tableau temp *burp* -1
    }else{
        for (int i = heigth; i > 0; i--)
        {
            for (int j = 0; j < width; j++)
            {
                    tempArray[i-1][j]=tempArray[i][j];
            }
        }
    }
}
//suppr line + 
void supprLine(int row,int ** permArray,int width, int heigth){
    for (int i = 0; i < width; i++)
    {
        permArray[row][i]=0;
    }
    for (int i = heigth; i > 0; i--)
    {
       for (int j = 0; j < width; j++)
       {
        permArray[i+1][j]=permArray[i][j];
       }
    }
}

void PartialClean(SDL_Renderer * renderer){

    if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE)){
        SDL_ExitWithError("Impossible de changer de couleur");
    }

    SDL_Rect FillBlack = {
        .x = WIDTH/4,
        .y = 0,
        .h = HEIGHT,
        .w = WIDTH
    };


    if (SDL_RenderFillRect(renderer, &FillBlack)){
        SDL_ExitWithError("Impossible de clear l'écran");
    }
}