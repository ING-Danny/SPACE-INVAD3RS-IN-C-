
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <stdint.h>
#include "conio.h"
#include "defalien.h"
#include "alien.h"


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


int get_max_sprite_width() {
    char **sprites[] = { squid, crab, saucer, shield, octopus, cannon };
    int count = sizeof(sprites) / sizeof(sprites[0]);
    int maxw = 0;

    for (int s = 0; s < count; s++) {
        int w = strlen(sprites[s][0]); 
        if (w > maxw) maxw = w;
    }
    return maxw;
}

int get_max_sprite_height() {
    char **sprites[] = { squid, crab, saucer, shield, octopus, cannon };
    int count = sizeof(sprites) / sizeof(sprites[0]);
    int maxh = 0;

    for (int s = 0; s < count; s++) {
        int h = 0;
        while (sprites[s][h][0] != '\0') h++;
        if (h > maxh) maxh = h;
    }
    return maxh;
}