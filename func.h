#ifndef A
#define A

#define HEIGHT 600
#define WIDTH 800


void SDL_ExitWithError(char * message);

void SDL_PrintVersion();

void SDL_ClearScreen(SDL_Renderer * renderer);

void SDL_WriteText(SDL_Renderer * renderer, int x, int y, int w, int h, SDL_Color color, char * text);

#endif