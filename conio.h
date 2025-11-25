/* Ruler 1         2         3         4         5         6         7        */

#ifndef	CONIO_H
#define CONIO_H
#include <stdint.h>

/********************************* Data types *********************************/

/* ------------------- Symbolic constants for color text -------------------- */

enum { RESET, BLACK = 30, RED, GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE };



/*********************** Prototypes of Public Functions ***********************/

/* -------------------------- Services in console --------------------------- */

void Clear_Screen();
void gotoxy( unsigned char, unsigned char );
void textcolor( int );
void Get_Console_Size(unsigned char *x, unsigned char *y);
void Set_Console_Size( uint8_t x, uint8_t y );
void Cursor( int status );

#endif /* CONIO_H */
