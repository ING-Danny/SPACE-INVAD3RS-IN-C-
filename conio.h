/* Ruler 1         2         3         4         5         6         7        */

#ifndef	CONIO_H
#define CONIO_H

/********************************* Data types *********************************/

/* ------------------- Symbolic constants for color text -------------------- */

enum { RESET, BLACK = 30, RED, GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE };



/*********************** Prototypes of Public Functions ***********************/

/* -------------------------- Services in console --------------------------- */

void clrscr();
void gotoxy( unsigned char, unsigned char );
void textcolor( int );

#endif /* CONIO_H */
