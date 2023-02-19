#ifndef A
#define A

#define HEIGHT 600
#define WIDTH 800


void SDL_ExitWithError(char * message);
void SDL_PrintVersion();
void SDL_ClearScreen(SDL_Renderer * renderer);
void testScreen(SDL_Renderer * renderer);
void SDL_WriteText(SDL_Renderer * renderer, int x, int y, int w, int h, SDL_Color color, char * text);
void SDL_WriteTextBuffered(SDL_Renderer * renderer,int x, int y, int w, int h, SDL_Color color, char * arraySTR);
int checkFileEmpty(char * file_path);
void writeInFile(char * file_path, int int_input);
char * readInFile(char * file_path);
void writeCharFile(char * file_path, char * input_string);
char * readInFileSized(char * file_path,int size);

#endif