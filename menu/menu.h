#ifndef C
#define C

void preMenu(SDL_Window * window, SDL_Renderer * renderer);
void menu(SDL_Window * window, SDL_Renderer * renderer);
void drawMenu(SDL_Window * window, SDL_Renderer * renderer, int choice);


int Escape ( SDL_Renderer * renderer);
void DrawEscape ( SDL_Renderer * renderer,int choice);

#endif