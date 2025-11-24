#include "alien.h"
#include "conio.h"
#include "defalien.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dibujar_aliens();

enum { SQUID_ROW, CRAB_ROW, OCTOPUS_ROW };

int main() {

  clrscr();
  dibujar_aliens();

  return 0;
}

void dibujar_aliens() {

#define COLS 3
#define ROWS 3
#define TOTAL (COLS * ROWS)

  ALIEN_T *alien[TOTAL];

  int baseX = 5;
  int baseY = 6;
  int sepX = 20;
  int sepY = 10;

  int idx = 0;

  clrscr();

  // squids primera fila
  for (int c = 0; c < COLS; c++, idx++) {
    alien[idx] = New_alien();
    Set_Aspect(alien[idx], &squid);
    Set_alien_color(alien[idx], GREEN);
    SetAlienLocation(alien[idx], baseX + c * sepX, baseY);
  }

  // segunda fila los crabs
  for (int c = 0; c < COLS; c++, idx++) {
    alien[idx] = New_alien();
    Set_Aspect(alien[idx], &crab);
    Set_alien_color(alien[idx], RED);
    SetAlienLocation(alien[idx], baseX + c * sepX, baseY + sepY);
  }

  //  TERCERA FILA  OCTOPUS

  for (int c = 0; c < COLS; c++, idx++) {
    alien[idx] = New_alien();
    Set_Aspect(alien[idx], &octopus);
    Set_alien_color(alien[idx], CYAN);
    SetAlienLocation(alien[idx], baseX + c * sepX, baseY + 2 * sepY);
  }

  /*  DIBUJAR Y LIBERAR LOS 9 ALIENS */
  for (int i = 0; i < TOTAL; i++)
    DrawAlien(alien[i]);
  for (int i = 0; i < TOTAL; i++)
    Free_alien(alien[i]);

  /*    SAUCER */
  ALIEN_T *ufo = New_alien();
  Set_Aspect(ufo, &saucer);
  Set_alien_color(ufo, CYAN);
  SetAlienLocation(ufo, baseX + sepX, baseY - 4); // arriba centrado
  DrawAlien(ufo);
  Free_alien(ufo);

  // --------- SHIELDS ----------
  ALIEN_T *sh[2];
  int shieldSpacing = 20;
  int firstShieldX = baseX + ((COLS - 1) * sepX) / 2 - shieldSpacing / 2;

  // Posición Y de los shields: relativa a la última fila de aliens
  int lastAlienY = baseY + 2 * sepY;
  int shieldY = lastAlienY + 6; // separación de 6 líneas debajo de los aliens

  for (int i = 0; i < 2; i++) {
    sh[i] = New_alien();
    Set_Aspect(sh[i], &shield);
    Set_alien_color(sh[i], GREEN);
    SetAlienLocation(sh[i], firstShieldX + i * shieldSpacing, shieldY);
    DrawAlien(sh[i]);
  }
  for (int i = 0; i < 2; i++)
    Free_alien(sh[i]);

  // --------- PLAYER (CANNON) ----------
  ALIEN_T *player = New_alien();
  Set_Aspect(player, &cannon);
  Set_alien_color(player, WHITE);

  // Centramos respecto a los aliens
  int playerX = baseX + ((COLS - 1) * sepX) / 2;
  int playerY = shieldY + 10; // un poco debajo de los shields
  SetAlienLocation(player, playerX, playerY);
  DrawAlien(player);
  Free_alien(player);
}