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

void rotation(int ** miniArray){
    int ** rotated_shape = malloc(sizeof(int *) * 3);
    for(int i = 0; i < 3; i++){
        rotated_shape[i] = malloc(sizeof(int) * 3);
        for (int j = 0; j < 3; j++){
            rotated_shape[i][j] = 0;
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int x = i;
            int y = j;
            int new_x = 3 - 1 - y;
            int new_y = x;
            rotated_shape[new_x][new_y] = miniArray[x][y];
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            miniArray[i][j]=rotated_shape[i][j];
        }
        free(rotated_shape[i]);
    }
    free(rotated_shape);
}


