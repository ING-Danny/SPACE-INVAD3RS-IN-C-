#ifndef DIBUJAR_ALIENS_H
#define DIBUJAR_ALIENS_H

#include "alien.h"

#define N_ALIENS 12
#define N_SHIELDS 3

typedef struct {
    ALIEN_T **aliens;
    int num_aliens;
    ALIEN_T *shields[N_SHIELDS];
    ALIEN_T *cannon;
} GameObjects;

// Inicializa aliens, shields y cannon
GameObjects *InitGameObjects(void);

// Loop principal del juego
void RunGameLoop(GameObjects *obj);

// Liberar memoria de los objetos del juego
void FreeGameObjects(GameObjects *obj);

#endif
