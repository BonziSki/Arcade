
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
#include<time.h>

#include "snake.h"
#include "../../func.h"



int ** createSnake(int size) {
    
    int midScreen = ((WIDTH / CASE_SIZE) % 2) ? (WIDTH / CASE_SIZE)/2 : ((WIDTH / CASE_SIZE) - 1)/2;
    printf("milieu de l'ecran : %d\n", midScreen);

    int ** temp = malloc(sizeof(int *) * size);

    //si la fonction malloc ne fonctionne pas correctement
    if (temp == NULL){
        printf("assignation de la mémoire échouée\n");
        return NULL;
    }

    for (int i = 0; i < size; i++){
        temp[i] = malloc(sizeof(int) * 2);

        //x
        temp[i][0] = midScreen - i;
        
        //y
        temp[i][1] = 10;
    }

    printf("serpent créé !\n#########################################\n");
    return temp;
}

void addSnakeNode(int *** snake, int size, int dir_h, int dir_v){
    //allocation d'un tableau avec un taille de + 1
    snake = realloc(snake, sizeof(int *) * (size + 1));

    //décalage de tout le tableau pour libérer la première case
    memmove(snake + 1, snake, (sizeof(int *) * size));

    //assignation des coordonnées de la nouvelles première case
    snake[0][0] = snake[1][0] + dir_h;
    snake[0][1] = snake[1][1] + dir_v;
}

void createFruit(Fruit * fruit, int ** snake, int size){
    
    fruit->x = (rand() % MAX_CASE_WIDTH);
    fruit->y = (rand() % MAX_CASE_HEIGHT);
    //on empeche que le fruit soit a l'extrémité

    

    int a = 1;
    int i = 0;

    while(a){
        if(fruit->x == snake[i][0]){
            if(fruit->y == snake[i][1]){
                fruit->x = rand() % MAX_CASE_WIDTH;
                fruit->y = rand() % MAX_CASE_HEIGHT;

                i = 0;
            }else{
                i++;
            }
        }else{
            i++;
        }
        
        //si on arrive au bout du serpent
        if(i == size){
            a = 0;
        }
    }
}



void viewAllNodes(int ** snake, int size){

    int i = 1;

    for (int i = 0; i < size; i++){
        if (i == 0){
            printf("[HEAD] snake node n°%d : x = %d | y = %d\n", i, snake[i][0], snake[i][1]);
        
        }else{
            printf("       snake node n°%d : x = %d | y = %d\n", i, snake[i][0], snake[i][1]);
        }
    }
    printf("\n");
}


void drawSnake(SDL_Renderer * renderer, int ** snake, int size, Fruit *fruit){


    //nettoyage de l'écran
    SDL_ClearScreen(renderer);

    //changement de couleur
    if (SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }

    //Dessin du terrain
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));

    //Dessin du snake
    viewAllNodes(snake, size);
    for (int i = 0; i < size; i++){

        rect->x = snake[i][0] * CASE_SIZE;
        rect->y = snake[i][1] * CASE_SIZE;
        rect->h = CASE_SIZE;
        rect->w = CASE_SIZE;

        SDL_RenderFillRect(renderer, rect);
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
    printf("############\n");
}


void mainLoopSnake(SDL_Window* window, SDL_Renderer * renderer){

    int size = BEGIN_SNAKE_SIZE;
    int ** snake = createSnake(size);

    Fruit * fruit = malloc(sizeof(Fruit));

    createFruit(fruit, snake, size);

    int dir_h = 1;
    //Directions horizontales:
    //  1 = droite
    // -1 = gauche
    //a initialisé à 1 au début toujours

    int dir_v = 0;
    //Directions horizontales:
    //  1 = bas
    // -1 = haut


    int quitsnake = 0;
    SDL_Event eventsnake;

    while(!quitsnake){
        if (updateSnake(snake, size, fruit, &dir_h, &dir_v) == 0){
            quitsnake = 1;
        };


        drawSnake(renderer, snake, size, fruit);
        SDL_Delay(2000);
    }

    //free de la mémoire
    for (int i = 0; i < size; i++){
        free(snake[i]);
    }
    
    free(snake);
    free(fruit);

};


int updateSnake(int ** snake, int size, Fruit * fruit, int * dir_h, int * dir_v){

    //vérification des entrées du user
    SDL_Event event;

    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
            //quitter le programme
            return 0;
        }
        if (event.type == SDL_KEYDOWN){
                //nécessite un cooldown entre les touches
            switch (event.key.keysym.sym){

                case SDLK_UP:
                    if(*dir_v != 1){
                        printf("UP\n");
                        *dir_v = -1;
                        *dir_h = 0;
                    }
                    break;

                case SDLK_DOWN:
                    if(*dir_v != -1){
                        printf("DOWN\n");
                        *dir_v = 1;
                        *dir_h = 0;
                    }
                    break;

                case SDLK_LEFT:
                    if(*dir_h != 1){
                        printf("LEFT\n");
                        *dir_h = -1;
                        *dir_v = 0;
                    }
                    break;

                case SDLK_RIGHT:
                    if(*dir_h != -1){
                        printf("RIGHT\n");
                        *dir_h = 1;
                        *dir_v = 0;
                    }
                    break;
                
                default:
                    break;
            }
        }
    }


    //Update de la position du snake en fonction de sa direction
    int tempX, tempX2;
    int tempY, tempY2;
    
    int firstLoop = 1;

    for (int i = 0; i < size; i++){
        if(i == 0){
            tempX = snake[i][0];
            tempY = snake[i][1];

            snake[i][0] = snake[i][0] + *dir_h;
            snake[i][1] = snake[i][1] + *dir_v;

            //vérification de collisions avec les côtés de la fenetre
            if ((snake[i][0] < 0 || snake[i][0] > MAX_CASE_WIDTH) || (snake[i][1] < 0 || snake[i][1] > MAX_CASE_HEIGHT)){
                printf("loose\n");
                return 0;
            }
        }else{
            tempX2 = snake[i][0];
            tempY2 = snake[i][1];

            snake[i][0] = tempX;
            snake[i][1] = tempY;

            tempX = tempX2;
            tempY = tempY2;
        }
        
    }
    


    //si il a mangé un fruit, augmenter sa taille et faire spawn un nouveau fruit
    if (snake[i][0] == fruit->x && snake[i][1] == fruit->y){

        addSnakeNode(&snake, size, *dir_h, *dir_v);
        createFruit(fruit, snake, size);
        //score++
    }

    
    
    return 1;
}


