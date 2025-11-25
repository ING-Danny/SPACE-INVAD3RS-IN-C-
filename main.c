#include "alien.h"
#include "conio.h"
#include "defalien.h"
#include "numeros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void dibujar_aliens();

enum { SQUID_ROW, CRAB_ROW, OCTOPUS_ROW };

int main() {

    unsigned char w, h;
    Get_Console_Size(&w, &h);

    Clear_Screen();
    dibujar_aliens(w, h);

  return 0;
}

void dibujar_aliens() {
    int N = 12; // Número de aliens por fila (squids, crabs, octopus)
    int spriteSpace = 3; // Separación horizontal exacta entre sprites
    int spriteWidthOnScreen = 8; // ancho real de cada sprite
    unsigned char W, H;
    Get_Console_Size(&W, &H);

    Clear_Screen();

    // ---------------------- S A U C E R ----------------------
    ALIEN_T *sc = New_alien();
    Set_Aspect(sc, &saucer);
    int sauW = sc->width, sauH = sc->height;
    int sauX = (W - sauW) / 2;
    int sauY = 1;

    Set_alien_color(sc, RED);
    SetAlienLocation(sc, sauX, sauY);
    DrawAlien(sc);
    Free_alien(sc);

    // ---------------------- CREAR ALIENS ----------------------
    ALIEN_T *sq = New_alien(); Set_Aspect(sq, &squid);
    ALIEN_T *cr = New_alien(); Set_Aspect(cr, &crab);
    ALIEN_T *oc = New_alien(); Set_Aspect(oc, &octopus);
    ALIEN_T *sh = New_alien(); Set_Aspect(sh, &shield);
    ALIEN_T *cn = New_alien(); Set_Aspect(cn, &cannon);

    int squidH = sq->height, crabH = cr->height, octopusH = oc->height;
    int shieldH = sh->height, cannonW = cn->width, cannonH = cn->height;

    // ---------------------- CALCULO DEL START X ----------------------
    int totalWidth = N * spriteWidthOnScreen + (N - 1) * spriteSpace;
    int startX = (W - totalWidth) / 2; // centrado

    // ---------------------- DIBUJAR S Q U I D S ----------------------
    int squidsY = sauY + sauH + 3;
    for (int i = 0; i < N; i++) {
        int x = startX + i * (spriteWidthOnScreen + spriteSpace);
        SetAlienLocation(sq, x, squidsY);
        Set_alien_color(sq, PURPLE);
        DrawAlien(sq);
    }
    Free_alien(sq);

    // ---------------------- DIBUJAR C R A B S ----------------------
    int crabsY = squidsY + squidH + 3;
    for (int i = 0; i < N; i++) {
        int x = startX + i * (spriteWidthOnScreen + spriteSpace);
        SetAlienLocation(cr, x, crabsY);
        Set_alien_color(cr, BLUE);
        DrawAlien(cr);
    }
    Free_alien(cr);

    // ---------------------- DIBUJAR O C T O P U S ----------------------
    int octopusY = crabsY + crabH + 3;
    for (int i = 0; i < N; i++) {
        int x = startX + i * (spriteWidthOnScreen + spriteSpace);
        SetAlienLocation(oc, x, octopusY);
        Set_alien_color(oc, CYAN);
        DrawAlien(oc);
    }
    Free_alien(oc);

    // ---------------------- DIBUJAR S H I E L D S ----------------------
    int shieldsY = octopusY + octopusH + 6;
    int N_shields = 3;
    int shieldW=sh->width;
    totalWidth = N_shields * shieldW + (N_shields - 1) * spriteSpace;
    startX = (W - totalWidth) / 2;

    for (int i = 0; i < N_shields; i++) {
        int x = startX + i * (shieldW + spriteSpace);
        SetAlienLocation(sh, x, shieldsY);
        Set_alien_color(sh, GREEN);
        DrawAlien(sh);
    }

    // ---------------------- DIBUJAR C A N N O N ----------------------
    int cannonY = shieldsY + shieldH + 7;
    int cannonX = (W - cannonW) / 2;
    SetAlienLocation(cn, cannonX, cannonY);
    Set_alien_color(cn, WHITE);
    DrawAlien(cn);
    Free_alien(cn);

    ALIEN_T *vida = New_alien();
    Set_Aspect(vida, &corazon);  // usa tu mini corazón definido antes

    int numVidas = 3;            // número de vidas
    int vidaSpace = 1;           // separación horizontal entre vidas
    int vidaW = vida->width;
    int vidaH = vida->height;

    // Ubicamos la primera vida desde la derecha
    int vidaX = W - (numVidas * vidaW + (numVidas - 1) * vidaSpace);
    int vidaY = sauY; // misma altura que el saucer

    for (int i = 0; i < numVidas; i++) {
        SetAlienLocation(vida, vidaX + i * (vidaW + vidaSpace), vidaY);
        Set_alien_color(vida, RED);
        DrawAlien(vida);
    }

    Free_alien(vida);

    ALIEN_T *num_izq = CreateNumber(0, RED, 5, sauY);
    Free_alien(num_izq);
}