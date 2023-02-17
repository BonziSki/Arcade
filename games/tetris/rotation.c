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

void rotation(int ** miniArray,int * x,int * y,int ** permArray){
    int l_empty=1;
    int r_empty=1;
    int can_rotate=1;
    int l_moveable=1;
    int r_moveable=1;   




    //init shape buffer
    int ** rotated_shape = malloc(sizeof(int *) * 3);
    for(int i = 0; i < 3; i++){
        rotated_shape[i] = malloc(sizeof(int) * 3);
        for (int j = 0; j < 3; j++){
            rotated_shape[i][j] = 0;
        }
    }
    //rotation
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int x = i;
            int y = j;
            int new_x = 3 - 1 - y;
            int new_y = x;
            rotated_shape[new_x][new_y] = miniArray[x][y];
        }
    }
    //check collision
    //DROITE
    if (*x>7)
    {
        r_moveable=0;
        for (int i = 0; i < 3; i++)
        {
            if (rotated_shape[i][2]!=0){
                r_empty=0;
            }
        }
        if (r_empty==1){
            //check permArray a gauche
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                    if (permArray[*y+i][*x-1+j]!=0){
                        if (rotated_shape[i][j]!=0){
                            can_rotate=0;
                        }
                    }
                } 
            } 
        }
    }else if(*x<0){
        l_moveable=0;
        //GAUCHE
        for (int i = 0; i < 3; i++)
        {
            if (rotated_shape[i][0]!=0){
                l_empty=0;
            }
        }
        if (l_empty==1){
            //check permArray a droite
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                    if (permArray[*y+i][*x+1+j]!=0){
                        if (rotated_shape[i][j]!=0){
                            can_rotate=0;
                        }
                    }
                } 
            } 
        }
    }else{
        l_moveable=0;
        r_moveable=0;
        //acutel
        for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                    if (permArray[*y+i][*x+j]!=0){
                        if (rotated_shape[i][j]!=0){
                            can_rotate=0;
                        }
                    }
                } 
            } 
        }
    if (can_rotate)
    {
        if (l_moveable)
        {
            *x-=1;
        }
        if (r_moveable)
        {
            *x+=1;
        }
        //shape=shape_buffer
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                miniArray[i][j]=rotated_shape[i][j];
            }
            free(rotated_shape[i]);
        }
        free(rotated_shape);
    }else{
        for (int i = 0; i < 3; i++) {
            free(rotated_shape[i]);
        }
        free(rotated_shape);
    }
}


