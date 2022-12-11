#ifndef A
#define A


#define HEIGHT 600
#define WIDTH 800


void SDL_PrintVersion();
void SDL_ExitWithError(char * message);
/*void escape(SDL_Window * window, SDL_Renderer * renderer);
    lorsque appuyer fenêtre de pause
    bouton 1 quitter
    bouton 2 continuer
*/
void clean(SDL_Window * window);
#endif