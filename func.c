//MAC
// #include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> 
// #include </opt/homebrew/Cellar/sdl_ttf/2.0.11_2/include/SDL/SDL_ttf.h>
//Windows
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#define BUFFER 9
//regarde si la taille du fichier est a 0 donc vide
int checkFileEmpty(char * file_path){
    FILE * fichier =NULL;
    fichier =fopen(file_path,"r");
    int size;
    if (fichier)
    {
        fseek(fichier,0,SEEK_END);
        size = ftell(fichier);
        fclose(fichier);
        return size;
    }else{
        return -1;
    }
    
}
//écrit le score dans fichier (la version ou un param est un int)
void writeInFile(char * file_path, int int_input){
    FILE * fichier =NULL;
    fichier =fopen(file_path,"w+");
    if (fichier != NULL){
        char char_buffer[BUFFER];
        sprintf(char_buffer,"%d",int_input);

        fputs(char_buffer,fichier);


        fclose(fichier);
    }else{
        printf("rater\n");
    }
}
//écriture dans fichier (la version ou un param est un string)
void writeCharFile(char * file_path, char * input_string){
    FILE * fichier =NULL;
    fichier =fopen(file_path,"w+");
    if (fichier != NULL){
        fputs(input_string,fichier);
        fclose(fichier);
    }else{
        printf("rater\n");
    }
}

//lecture de première ligne d'un fichier (n'est utilisé que pour le score qui ne dépasse généralement pas plus de 9 charactères)
char * readInFile(char * file_path){
    FILE * fichier =NULL;
    fichier =fopen(file_path,"r");
    char * chaine = malloc(sizeof(char)*BUFFER);
    int size;
    if (fichier != NULL){

        fgets(chaine,BUFFER-1,fichier);
        //Fermeture du fichier
        fclose(fichier);
        return chaine;
    }else{
        printf("rater\n");
    }
}
//read tout un file et envoyé en liste
char * readInFileSized(char * file_path,int file_size){
    FILE * fichier =NULL;
    fichier =fopen(file_path,"r");
    char * chaine = malloc(sizeof(char)*file_size);
    if (fichier != NULL){
        int cpt=0;
        while ((chaine[cpt]=fgetc(fichier))!=EOF)
        {
            cpt++;
        }
        //Fermeture du fichier
        fclose(fichier);
        return chaine;
    }else{
        printf("rater\n");
    }
}

void SDL_ExitWithError(char * message){
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void SDL_PrintVersion(){
    SDL_version nb;
    SDL_VERSION(&nb);

    printf("SDL %d.%d.%d \n", nb.major, nb.minor, nb.patch);
}

void SDL_ClearScreen(SDL_Renderer * renderer){

    if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE)){
        SDL_ExitWithError("Impossible de changer de couleur");
    }

    SDL_Rect FillBlack = {
        .x = 0,
        .y = 0,
        .h = HEIGHT,
        .w = WIDTH
    };


    if (SDL_RenderFillRect(renderer, &FillBlack)){
        SDL_ExitWithError("Impossible de clear l'écran");
    }

    // SDL_RenderPresent(renderer);


}

void testScreen(SDL_Renderer * renderer){

    if (SDL_SetRenderDrawColor(renderer, 0, 124, 255, SDL_ALPHA_OPAQUE)){
        SDL_ExitWithError("Impossible de changer de couleur");
    }

    SDL_Rect FillBlack = {
        .x = 0,
        .y = 0,
        .h = HEIGHT,
        .w = WIDTH / 2
    };


    if (SDL_RenderFillRect(renderer, &FillBlack)){
        SDL_ExitWithError("Impossible de clear l'écran");
    }

    SDL_RenderPresent(renderer);
}

void SDL_WriteText(SDL_Renderer * renderer, int x, int y, int w, int h, SDL_Color color, char * text){

    //chargement de la police d'écriture
    TTF_Font * font = NULL;
    
    font = TTF_OpenFont("./ressources/font/ARCADEPI.TTF", 20);

    if(font == NULL){
        SDL_ExitWithError("Chargement de la police d'écriture");
    }

    //création de la surface
    SDL_Surface * surface = NULL;

    surface = TTF_RenderText_Blended(font, text, color);

    if (surface == NULL){
        SDL_ExitWithError("Chargement du texte sur la surface");
    }


    //Création de la texture
    SDL_Texture * texture = NULL;

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (texture == NULL){
        SDL_ExitWithError("Chargement de la texture");
    }


    //Création du rectangle
    SDL_Rect rect = {x, y, w, h};

    //Recopie de la texture sur la window
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    //Mise à jour de la fenêtre
    SDL_RenderPresent(renderer);


    //Free

    //fermeture de la texture
    SDL_DestroyTexture(texture);
    
    //fermeture de la surface
    SDL_FreeSurface(surface);

    //Fermeture de la police
    TTF_CloseFont(font);

}
void SDL_WriteTextBuffered(SDL_Renderer * renderer,int x, int y, int w, int h, SDL_Color color,char * arraySTR){

    char * buffer = malloc(sizeof(char)*SDL_strlen(arraySTR));
    sprintf(buffer,"%s",arraySTR);
    SDL_WriteText(renderer, x, y, w, h, color, buffer);
    free(buffer);
}