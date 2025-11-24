
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "conio.h"
#include "defalien.h"
#include "alien.h"




typedef struct ALIEN_T {
    int color;
    unsigned char posx;
    unsigned char posy;
    char *(*aspect)[];
    unsigned char width;
    unsigned char height;

} ALIEN_T;

//dusando la creacion dinamicos 
ALIEN_T *New_alien(){

    return (ALIEN_T *)malloc(sizeof(ALIEN_T));


}
//liberando memoriaa

int Free_alien(ALIEN_T * this){

    free(this);

    return 1; 

    
}

ALIEN_T* Set_Aspect(ALIEN_T* this,char *(*aspect)[] ){

this->aspect=aspect;

//hallamos sus magnitudes 
#ifdef UNICODE
this->width=strlen((*this->aspect)[0])/3;
#else
this->width=strlen((*this->aspect)[0]);
#endif

this->height=0;

while((*this->aspect)[this->height][0] != '\0') this->height++;
return this;

}

ALIEN_T *Set_alien_color(ALIEN_T *this, int color){
    this->color=color;
    return this;   
}

ALIEN_T * SetAlienLocation(ALIEN_T *this, unsigned char x, unsigned char y){
    this->posx=x;
    this->posy=y;
    return this; 


}

void DrawAlien(ALIEN_T *this){

    textcolor(this->color);

    for(int i=0; *(*this->aspect)[i]!='\0';i++){
        gotoxy(this->posx,this->posy+i);
        
        printf("%s\n",(*this->aspect)[i]);
        
    }
   


}

