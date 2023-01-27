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
 
void DrawControl(SDL_Renderer * renderer){

}


int ** createTmpTable(int height, int width){
    int ** tempArray = malloc(sizeof(int *) * height);
    for (int i = 0; i < height; i++)
    {
        tempArray[i]=malloc(sizeof(int)*width);
    }
    
    return tempArray;
}
int ** createPermTable(int height, int width){
    int ** permArray = malloc(sizeof(int *) * height);
    for (int i = 0; i < height; i++)
    {
        permArray[i]=malloc(sizeof(int)*width);
    }
    
    return permArray;
}


void updateTetris(int ** tempArray, int ** permArray,int heigth, int width){  
    int flag =0;
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
            if (flag==1)
            {
                break;
            }
        }
        if (flag==1)
        {
            break;
        }   
    }
    //copie tableau temp dans perm moins cellule vide
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
        //
        for (int i = 0; i < heigth; i++)
            {
                for (int j = 0; j < width; j++)
                {

                }
            }
        //sinon descendre tableau temp *burp* -1
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

void supprLine(int row,int ** permArray,int width){
    
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