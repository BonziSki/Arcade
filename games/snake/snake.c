
//--------- SDL ---------
//MAC
#include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> 
#include </opt/homebrew/Cellar/sdl_ttf/2.0.11_2/include/SDL/SDL_ttf.h>
 
//Windows
// #include <SDL2/SDL.h> 
// #include <SDL2/SDL_ttf.h>

//-----------------------

#include <stdio.h>
#include <stdlib.h>

#include "snake.h"
#include "../../func.h"



<<<<<<< HEAD

typedef struct Snake Snake;
struct Snake
{
    int x;
    int y;
    Snake * next;
};
=======
>>>>>>> cf960beb33f641228e7223e3383ec004f27a0bba



Snake * createSnake() {

    printf("\n\nCréation du serpent : \n");
    
    int midScreen = ((WIDTH / CASE_SIZE) % 2) ? (WIDTH / CASE_SIZE)/2 : ((WIDTH / CASE_SIZE) - 1)/2;
    printf("milieu de l'écran : %d\n", midScreen);

    Snake* temp = NULL;


    for (int i = midScreen; i > midScreen - 4; i--){
        Snake* snake = malloc(sizeof(Snake));

        snake->y = 10;
        snake->x = i;
        snake->next = temp;
        temp = snake;

        printf("noeud n°%d : x = %d | y = %d | next = %p\n", i, snake->x, snake->y, snake->next);
        printf("temp = %p\n", temp);
    }
    return temp;
}

void createFruit(Fruit * fruit, Snake * snake){
    
    fruit->x = rand() % MAX_CASE_WIDTH;
    fruit->y = rand() % MAX_CASE_HEIGHT;

    Snake * tempSnake = snake;

    int a = 1;

    while (a){
        if (fruit->x == tempSnake->x){
            if (fruit->y == tempSnake->y){
                fruit->x = rand() % MAX_CASE_WIDTH;
                fruit->y = rand() % MAX_CASE_HEIGHT;

                tempSnake = snake;
            }
        }

        tempSnake = tempSnake->next; 

        if(tempSnake->next != NULL){
            a = 0;
        }
    }
};


void drawSnake(SDL_Renderer * renderer, Snake * snake, Fruit *fruit){

    Snake * tempSnake = snake;


    //nettoyage de l'écran
    SDL_ClearScreen(renderer);

    //changement de couleur
    if (SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }

    //Dessin du terrain
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));

    //Dessin du snake
    while (tempSnake->next != NULL){
        printf("print snake node : x = %d | y = %d | next = %p\n", tempSnake->x, tempSnake->y, tempSnake->next);

        rect->x = tempSnake->x * CASE_SIZE;
        rect->y = tempSnake->y * CASE_SIZE;
        rect->h = CASE_SIZE;
        rect->w = CASE_SIZE;

        SDL_RenderFillRect(renderer, rect);

        tempSnake = tempSnake->next;
    }
    

    //changement de couleur
    if (SDL_SetRenderDrawColor(renderer, 200, 20, 20, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }

    //Dessin fruit
    rect->x = fruit->x * CASE_SIZE;
    rect->y = fruit->y * CASE_SIZE;
    rect->h = CASE_SIZE;
    rect->w = CASE_SIZE;
    SDL_RenderFillRect(renderer, rect);

    free(rect);

    //affichage de tous les éléments
    SDL_RenderPresent(renderer);
}

void drawTest(){

    SDL_Rect * rect = malloc(sizeof(SDL_Rect));

    rect->h= 25;
    rect->w= 25;


    for (int i = 0; i < MAX_CASE_HEIGHT; i++){
        for (int j = 0; j < MAX_CASE_WIDTH; j++){
            rect->x = j;
            rect->y = i;
        }
    }
}

void mainLoopSnake(SDL_Window* window, SDL_Renderer * renderer){

    Snake * snake = createSnake();

    printf("\n%p\n", snake);


    Fruit * fruit = malloc(sizeof(Fruit));
    createFruit(fruit, snake);

    printf("\nFruit : x = %d | y = %d", fruit->x, fruit->y);


    drawSnake(renderer, snake, fruit);
    SDL_Delay(1000);

    free(snake);
    free(fruit);

};

int updateSnake(Snake * Snake, Fruit * Fruit);






















































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