#ifndef ALIEN_H
#define ALIEN_H

typedef struct ALIEN_T {
    int color;
    unsigned char posx;
    unsigned char posy;
    char *(*aspect)[];
    unsigned char width;
    unsigned char height;
    int movible;
    int dx;

} ALIEN_T;

/* ---- Métodos ---- */
ALIEN_T * New_alien();
int Free_alien(ALIEN_T *);

ALIEN_T * Set_Aspect(ALIEN_T *, char *(*)[]);
ALIEN_T * Set_alien_color(ALIEN_T *, int);
ALIEN_T * SetAlienLocation(ALIEN_T *, unsigned char, unsigned char);

int get_max_sprite_width();
int get_max_sprite_height();

void DrawAlien(ALIEN_T *);

#endif