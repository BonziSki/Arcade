//MAC
// #include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> 
// #include </opt/homebrew/Cellar/sdl_ttf/2.0.11_2/include/SDL/SDL_ttf.h>
//Windows
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tetris.h"
#include "../../func.h"
#include "../../menu/menu.h"

void print_tabl(int ** tabl,int width, int heigth){
    printf("#######\n");
    for(int i=0; i<heigth;i++){
        for(int j =0; j<4;width++){
            printf(" %d",tabl[i][j]);
        }
        printf("\n");
    }
    printf("#######\n");
}
void pushX(int tabl [4][4]){
    //push table +1 vers droite
    for(int i=0; i<4;i++){
        for(int j =3; j>0;j--){
            tabl[i][j]=tabl[i][j-1];
            tabl[i][j-1]=0;
        }
        tabl[i][0]=0;
    }
}
void pushY(int tabl [4][4]){
    //push table +1 vers haut
    for(int i=0; i<4;i++){
        for(int j =0; j<4;j++){
            tabl[i][j]=tabl[i+1][j];
            if(i<2){
                tabl[i+1][j]=0;
            }
        }
    }
    for(int i=0; i<4;i++){
        tabl[3][i]=0;
    }
}
void copyArrayIntoDefined(int tabl_source[4][4],int tabl_dest[4][4]){
    for(int i=0; i<4;i++){
        for(int j =0; j<4;j++){
                tabl_dest[i][j]=tabl_source[i][j];
            }
    }
}
void rotation(int tabl [4][4]){
    int row_length=0;
    int col_length=0;
    int flag_row=0;
    int flag_col=0;
    for(int i=0; i<4;i++){
        for(int j =0; j<4;j++){
                if(tabl[i][j]!=0){
                    flag_row=1;
                }
                if(tabl[j][i]!=0){
                    flag_col=1;
                }
            }
            if(flag_row!=0){
                flag_row=0;
                row_length++;
            }
            if(flag_col!=0){
                flag_col=0;
                col_length++;
            }
    }
    int temp [4][4]= {
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,0}
    };
    if(row_length<3 && col_length<3){
        //cube donc pas de rotation
        goto OUT;
    }
    if(row_length>3 && col_length<2 || row_length<2 && col_length>3){
        //line piece rotation complete
        for(int i=0; i<4;i++){
            for(int j =0; j<4;j++){
                //x,y {j,i} 
                temp[j][i]=tabl[i][j];
            }
        }
    }
    if(row_length==3 && col_length==2){
        // 0 0 1 0
        // 0 1 1 0 
        // 0 0 1 0
        // 0 0 0 0
        for(int i=0; i<4;i++){
            for(int j =0; j<4;j++){
                //x,y {j,i} 
                temp[j][i]=tabl[i][j];
            }
        }
        pushX(temp);
        pushY(temp);
    }
    if(row_length==2 && col_length==3){
        // 0 0 1 0
        // 0 1 1 1
        // 0 0 0 0
        // 0 0 0 0
        
        for(int i=0; i<4;i++){
            for(int j =0; j<4;j++){
                temp[i][j]=tabl[3-j][i];
            }
        }
        
        pushY(temp);
    }

    copyArrayIntoDefined(temp,tabl);
    OUT:
    printf("");
    //c'est moche mais je contourne une contrainte du C de cette façon
}
int ** getTablInTabl(int ** sourceArray,int heigth, int width){
    //création du tableau tampon
    int ** tempArray = malloc(sizeof(int *) * 4);
    for (int i = 0; i < 4; i++){
        tempArray[i]=malloc(sizeof(int)*4);
        for (int j = 0; j < 4; j++){
            tempArray[i][j]=0;
        }
    }
    int finished_flag =0;
    int found_flag=0;
    int cpt1=0;
    int cpt2=0;

    for (int i = 0; i < heigth; i++){
        for (int j = 0; j < width; j++){
            if (sourceArray[i][j]!=0){
                found_flag=1;
                tempArray[cpt1][cpt2]=sourceArray[i][j];
                cpt1++;
            }
        }
    }
    //print_tabl(tempArray,4,4);
    printf("cpt1= %d, cpt2 = %d, temparray[0][0]=%d",cpt1,cpt2,tempArray[0][0]);
    return tempArray;
}
// int main()
// {
//     int tabl[4][4] = {
//                 {0,0,1,0},
//                 {0,0,1,0},
//                 {0,1,1,0},
//                 {0,0,0,0}
//     };
//     print_tabl(tabl);
//     rotation(tabl);
//     print_tabl(tabl);
//     rotation(tabl);
//     print_tabl(tabl);
//     rotation(tabl);
//     print_tabl(tabl);
//     rotation(tabl);
//     print_tabl(tabl);
    

//     return 0;
// }