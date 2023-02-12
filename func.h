#ifndef A
#define A

#define HEIGHT 600
#define WIDTH 800

#include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> //MAC
#include </opt/homebrew/Cellar/sdl_ttf/2.0.11_2/include/SDL/SDL_ttf.h>
// #include <SDL2/SDL.h>  //Windows
// #include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "func.h"

void SDL_ExitWithError(char * message);

void SDL_PrintVersion();

void SDL_ClearScreen(SDL_Renderer * renderer);

void SDL_WriteText(SDL_Renderer * renderer, int x, int y, int w, int h, SDL_Color color, char * text);

#endif