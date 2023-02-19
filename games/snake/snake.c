
//MAC
// #include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> 
// #include </opt/homebrew/Cellar/sdl_ttf/2.0.11_2/include/SDL/SDL_ttf.h>
//Windows
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "snake.h"
#include "../../func.h"
#include "../../menu/menu.h"
#include <string.h>

//fonction de création de la structure snake
Snake * createSnake() {

    //calcul du milieu de l'écran
    int midScreen = ((WIDTH / CASE_SIZE) % 2) ? (WIDTH / CASE_SIZE)/2 : ((WIDTH / CASE_SIZE) - 1)/2;

    Snake * temp = NULL;

    //création des noeud du snake
    for (int i = midScreen; i > midScreen - 3; i--){
        Snake * snake = malloc(sizeof(Snake));

        snake->y = 10;
        snake->x = i;
        snake->next = temp;
        temp = snake;
    }
    return temp;
}

//fonction d'ajout de noeud à la structure snake
Snake * addSnakeNode(Snake * snake,int dir_h,int dir_v){
    Snake * newSnake = malloc(sizeof(Snake));
    newSnake->x = snake->x + dir_h;
    newSnake->y = snake->y + dir_v;
    newSnake->next=snake;
    
    return newSnake;
}


//fonction de création de la structure fruit
void createFruit(Fruit * fruit, Snake * snake){
    
    //position aléatoire
    fruit->x = (rand() % MAX_CASE_WIDTH);
    fruit->y = (rand() % MAX_CASE_HEIGHT);

    Snake * tempSnake = snake;

    int a = 1;

    //on empêche le fruit de spawn dans le corps du snake
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
}

//fonction qui permet de visualiser tous les noeud du snake
void viewAllNodes(Snake * snake){
    Snake * tempSnake = snake;
    int nextNodeNull = 0;
    int i = 1;
    printf("[HEAD]");

    while (!nextNodeNull){
        printf("snake node n°%d : x = %d | y = %d | next = %p\n", i, tempSnake->x, tempSnake->y, tempSnake->next);
        i++;

        if (tempSnake->next == NULL){
            nextNodeNull = 1;
        }

        tempSnake = tempSnake->next;
    }
    printf("\n");
}

//fonction de dessin
void drawSnake(SDL_Renderer * renderer, Snake * snake, Fruit *fruit, int * score){

    Snake * tempSnake = snake;


    //nettoyage de l'écran
    SDL_ClearScreen(renderer);

    //changement de couleur
    if (SDL_SetRenderDrawColor(renderer, 200, 180, 180, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }

    //Dessin du terrain
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));

    //Dessin de tous les noeuds du snake
    int nextNodeNull = 0;

    while (!nextNodeNull){
        //printf("print snake node : x = %d | y = %d | next = %p\n", tempSnake->x, tempSnake->y, tempSnake->next);
        
        rect->x = tempSnake->x * CASE_SIZE;
        rect->y = tempSnake->y * CASE_SIZE;
        rect->h = CASE_SIZE;
        rect->w = CASE_SIZE;
        //printf("rect x= %d y=%d h=%d w=%d\n",rect->x,rect->y,rect->h,rect->w);
        SDL_RenderFillRect(renderer, rect);
        

        if (tempSnake->next == NULL){
            nextNodeNull = 1;
        }

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


    //Dessin du score
    char buffer[12];
    sprintf(buffer, "Score : %d", *score);

    SDL_Color white = {180, 180, 200};

    SDL_WriteText(renderer, 10, 10, 50, 20, white, buffer);

    //affichage de tous les éléments
    SDL_RenderPresent(renderer);

}

//fonciton main
void mainLoopSnake(SDL_Window* window, SDL_Renderer * renderer,int speed_modifier){

    Snake * snake = createSnake();

    Fruit * fruit = malloc(sizeof(Fruit));
    createFruit(fruit, snake);

    int dir_h = 1;
    //Directions horizontales:
    //  1 = droite
    // -1 = gauche
    //a initialisé à 1 au début toujours

    int dir_v = 0;
    //Directions horizontales:
    //  1 = bas
    // -1 = haut

    int score = 0;


    int quitsnake = 0;
    int update =1;
    SDL_Event eventsnake;

    while(!quitsnake){
        update = updateSnake(renderer, snake, &snake, &score, fruit, &dir_h, &dir_v);

        if (update == 0){
            //le joueur a perdu
            if(gameOverMenuSnake(renderer, &score) == 1){
                printf("\n\nau revoir !\n");
                //free du serpent
                freeSnake(snake);
                //free du fruit
                free(fruit);
                //quitter le jeu snake
                quitsnake = 1;
                    
            }else{
            //restart le jeu
                //on refait le snake entièrement pour repartir à zero
                freeSnake(snake);
                
                snake = createSnake();

                int dir_h = 1;

                int dir_v = 0;

                int score = 0;
            }

        }else if (update == -1){
            //sortie manuel du joeur
            printf("\n\nau revoir !\n");
            //free du serpent
            freeSnake(snake);
            //free du fruit
            free(fruit);
            //quitter le jeu snake
            quitsnake = 1;
        }

        drawSnake(renderer, snake, fruit, &score);

        SDL_Delay(200 - (speed_modifier * 10));
    }
}

//fonction de free du snake
void freeSnake(Snake * snake){
    int nextNodeNull = 0;

    //on sauvegarde les prochains noeuds
    Snake * nextSnake = snake->next;
    Snake * nextNextSnake = nextSnake->next;

    //on free le noeud actuel
    free(snake);
    
    //tant que le prochain noeud n'est pas le dernier, on free le noeud
    while(!nextNodeNull){
        free(nextSnake);

        nextSnake = nextNextSnake;
        nextNextSnake = nextSnake->next;

        if (nextNextSnake == NULL){
            free(nextSnake);
            nextNodeNull = 1;
        }
    }
}

//fonction de gameover
int gameOverMenuSnake(SDL_Renderer * renderer, int * score){
    int quit = 0;
    int choice = 0;
    SDL_Event event;
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));

    while (!quit){
    //Dessin du menu
        //clear de la fenetre
        SDL_ClearScreen(renderer);

        //changement de couleur du renderer
        if (SDL_SetRenderDrawColor(renderer, 255, 0,0, SDL_ALPHA_OPAQUE) != 0){
            SDL_ExitWithError("Changement de couleur du rendu");
        }

        //rectangles de choix
        rect->w = 80;
        rect->h = 60;
        rect->x = 300;

        for (int i = 0; i < 2; i++){
            //on change la couleur du rectangle correspondant au choix du user
            if (choice == i){
                if (SDL_SetRenderDrawColor(renderer, 0, 255,0, SDL_ALPHA_OPAQUE) != 0){
                    SDL_ExitWithError("Changement de couleur du rendu");
                }
            }
            
            //calcul du y du rectangle
            rect->y = 140 + (80 + (rect->h * i * 2));

            //rendu du rectangle
            SDL_RenderFillRect(renderer, rect);

            //reset de la couleur
            if (SDL_SetRenderDrawColor(renderer, 255, 0,0, SDL_ALPHA_OPAQUE) != 0){
                SDL_ExitWithError("Changement de couleur du rendu");
            }
        }

        //deuxieme rectangle
        rect->w = 240;
        rect->h = 80;
        rect->x = WIDTH/2-rect->w/2;
        rect->y = 100;

        //rendu du rectangle
        SDL_RenderFillRect(renderer, rect);
        free(rect);
        //recentrer les zones   
        SDL_Color greyWhite = {200, 200, 200};
        char * dico[] = {"voulez vous rejouer ?","oui","non"};

        SDL_WriteTextBuffered(renderer,300,120,150,30,greyWhite,dico[0]);
        SDL_WriteTextBuffered(renderer,310,230,40,40,greyWhite,dico[1]);
        SDL_WriteTextBuffered(renderer,310,340,40,40,greyWhite,dico[2]);


        //Ecriture score dans fichier
        //print score
        char char_buffer[9];
        sprintf(char_buffer, "%d", *score);
        SDL_WriteTextBuffered(renderer, 620, 420, 40, 40, greyWhite, char_buffer);
        //score :
        SDL_WriteTextBuffered(renderer, 520, 420, 80, 40, greyWhite, "score :");
        // highscore :
        SDL_WriteTextBuffered(renderer, 500, 460, 100, 40, greyWhite, "highscore :");
        //print highscore
        if (checkFileEmpty("ressources/score/score_snake.txt") > 0){
            if(atoi(readInFile("ressources/score/score_snake.txt")) < *score){
                writeInFile("ressources/score/score_snake.txt", *score);
                SDL_WriteTextBuffered(renderer, 620, 460, 40, 40, greyWhite, char_buffer);
            }else{
                SDL_WriteTextBuffered(renderer, 620, 460, 40, 40, greyWhite, readInFile("ressources/score/score_snake.txt"));
            }
            
        }else{
            writeInFile("ressources/score/score_snake.txt", *score);
            SDL_WriteTextBuffered(renderer, 620, 460, 40, 40, greyWhite, char_buffer);
        }
        SDL_RenderPresent(renderer);



        //gestion des choix du user
        while (SDL_PollEvent(&event)){
            switch (event.type){

                case SDL_QUIT:
                    return 0;
                    break; 

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym){

                        case SDLK_DOWN:
                            if (choice < 1){
                                choice++;
                                printf("choice : %d\n",choice);
                            }
                            break;

                        case SDLK_UP:
                            if (choice > 0){
                                choice--;
                                printf("choice : %d\n",choice);
                            }
                            break;

                        case SDLK_RETURN:
                            printf("\nENTRER\n");
                            return choice;
                            break;
                    }
                    break;
            }
        }
    }
    return 0;
}

//fonction d'update
int updateSnake(SDL_Renderer * renderer, Snake * snake, Snake ** snake_pointer, int * score, Fruit * fruit, int * dir_h, int * dir_v){

    //vérification des entrées du user
    SDL_Event event;

    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
            //quitter le programme
            return -1;
        }
        if (event.type == SDL_KEYDOWN){
                //nécessite un cooldown entre les touches
            switch (event.key.keysym.sym){

                case SDLK_ESCAPE:
                        if(Escape(renderer) == 0){
                            return -1;
                        }
                    break;

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
    int nextNodeNull = 0;
    int firstLoop = 1;
    Snake * tempSnake = snake;

    while (!nextNodeNull){

        if (firstLoop){
            tempX = tempSnake->x;
            tempY = tempSnake->y;

            tempSnake->x = tempSnake->x + *dir_h;
            tempSnake->y = tempSnake->y + *dir_v;

            //vérification de collisions avec les côtés de la fenetre
            if ((snake->x < 0 || snake->x >= MAX_CASE_WIDTH) || (snake->y < 0 || snake->y >= MAX_CASE_HEIGHT)){
                printf("loose\n");
                return 0;
            }

            //vérification si le serpent s'est mangé lui-même
            if (*score > 0){
                int nextNodeNull = 0;
                Snake * verifSnake = tempSnake->next;

                while (!nextNodeNull){
                    if (tempSnake->x == verifSnake->x){
                        if (tempSnake->y == verifSnake->y){
                            printf("loose\n");
                            return 0;
                        }
                    }
                    

                    if (verifSnake->next == NULL){
                        nextNodeNull = 1;
                    }

                    verifSnake = verifSnake->next;
                
                }
            }
            firstLoop = 0;

        }else{
            tempX2 = tempSnake->x;
            tempY2 = tempSnake->y;

            tempSnake->x = tempX;
            tempSnake->y = tempY;

            tempX = tempX2;
            tempY = tempY2;

        }
        

        if (tempSnake->next == NULL){
            nextNodeNull = 1;
        }
        
        tempSnake = tempSnake->next;
    }
    
    


    //si il a mangé un fruit, augmenter sa taille et faire spawn un nouveau fruit
    if (snake->x == fruit->x && snake->y == fruit->y){
        //ajout d'un noeud au snake
        *snake_pointer = addSnakeNode(snake,*dir_h,*dir_v);

        //création d'un nouveau fruit
        createFruit(fruit,snake);

        //incrémentation du score
        *score = *score + 1;
    }
    
    return 1;
}
