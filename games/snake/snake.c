//MAC
#include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> 
#include </opt/homebrew/Cellar/sdl_ttf/2.0.11_2/include/SDL/SDL_ttf.h>
 
//Windows
// #include <SDL2/SDL.h> 
// #include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include "snake.h"
#include "../../func.h"
// #include <time.h>

#define WIDTH 800





Snake* initializeSnake() {
    int mdScreen = ((WIDTH / 25) % 2) ? (WIDTH / 25)/2 : ((WIDTH / 25) - 1)/2;
    Snake* temp = NULL;
    for (int i = mdScreen; i <mdScreen-4; i--)
    {
        Snake* snake = malloc(sizeof(Snake));
        snake->y=10;
        snake->x=i;
        snake->next = temp;
        temp = snake;
    }
    return temp;
}

void initializeFruit(Fruit * fruit){
    
    fruit->x= rand()%32;
    fruit->y=rand()%24;
};

// void SDL_ClearScreen(SDL_Renderer * renderer){
//     if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE)){
//         SDL_ExitWithError("Impossible de changer de couleur");
//     }

//     SDL_Rect FillBlack = {
//         .x = 0,
//         .y = 0,
//         .h = HEIGHT,
//         .w = WIDTH
//     };
//     if (SDL_RenderFillRect(renderer, &FillBlack)){
//         SDL_ExitWithError("Impossible de clear l'écran");
//     }

//     // SDL_RenderPresent(renderer);

// }

void drawSnake(Snake * snake, Fruit *fruit, SDL_Renderer * renderer){
    //nettoyage de l'écran
    SDL_ClearScreen(renderer);

    //changement de couleur
    if (SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }

    //Dessin du terrain
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));

    //Dessin du snake
    rect->x= snake->x;
    rect->y= snake->y;
    rect->h= 25;
    rect->w= 25;

    SDL_RenderFillRect(renderer, rect);

    //Dessin fruit
    rect->x= fruit->x;
    rect->y= fruit->y;
    rect->h= 25;
    rect->w= 25;
    SDL_RenderFillRect(renderer, rect);

    free(rect);

    //affichage de tous les éléments
    SDL_RenderPresent(renderer);
}

void mainLoopSnake(SDL_Window* window, SDL_Renderer * renderer){
    Snake *snake = initializeSnake();
    Fruit *fruit = malloc(sizeof(Fruit));
    initializeFruit(fruit);

    drawSnake(snake, fruit, renderer);
    SDL_Delay(5000);

};

// int updateSnake(Snake * Snake, Fruit * Fruit);






















































// void insertBeginning(Snake* snake, int x, int y) {
    
//     if (snake->head == NULL) {
        
//         Node* node = malloc(sizeof(Node));
//         if (node != NULL) {
//             node->next = snake->tail;
//             node->body.x = x;
//             node->body.y = y;
//             node->body.w = 25;
//             node->body.h = 25;
//             snake->head = node;
//         }
//         return;
//     }

//     else {
//         Node* temp = snake->head;
//         Node* node = malloc(sizeof(Node));
//         if (node != NULL) {
//             node->body.x = x;
//             node->body.y = y;
//             node->body.w = 25;
//             node->body.h = 25;
//             node->next = snake->head;
//             snake->head = node;
//         }
        
//     }
    
// }

// void insertEnd(Snake* snake, int x, int y) {

//     if (snake->tail == NULL) {
//         Node* node = malloc(sizeof(Node));
//         node->next = NULL;
//         snake->head->next = node;
//         node->body.x = x;
//         node->body.y = y;
//         node->body.w = 25;
//         node->body.h = 25;
//         snake->tail = node;
//     }

//     else {
//         Node* node = malloc(sizeof(Node));
//         if (node != NULL) {
//             node->next = NULL;
//             node->body.x = x;
//             node->body.y = y;
//             node->body.w = 25;
//             node->body.h = 25;
//             snake->tail->next = node;
//             snake->tail = node;
//         }
        
//     }
// }

// void deleteBeginning(Snake* snake) {
    
//     if (snake->head != NULL) {
//         Node* temp = snake->head;
//         snake->head = snake->head->next;
//         free(temp);
//     }
// }

// void deleteEnd(Snake* snake) {

//     if (snake->tail != NULL) {
//         Node* temp = snake->head;
//         while (temp->next != snake->tail) {
//             temp = temp->next;
//         }
//         snake->tail = temp;
//         free(temp);
//     }

// }