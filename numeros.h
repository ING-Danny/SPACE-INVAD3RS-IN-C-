#ifndef NUMEROS_H
#define NUMEROS_H

#include "alien.h"

ALIEN_T *CreateNumber(int n, int color, unsigned char x, unsigned char y);



// Cada número es un arreglo de strings (mini sprite)
extern char *numero0[];
extern char *numero1[];
extern char *numero2[];
extern char *numero3[];
extern char *numero4[];
extern char *numero5[];
extern char *numero6[];
extern char *numero7[];
extern char *numero8[];
extern char *numero9[];

ALIEN_T *CreateNumber(int n, int color, unsigned char x, unsigned char y);

#endif