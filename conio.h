/* Ruler 1         2         3         4         5         6         7        */

#ifndef	CONIO_H
#define CONIO_H
#include <stdint.h>

/********************************* Data types *********************************/

/* ------------------- Symbolic constants for color text -------------------- */

enum { RESET, BLACK = 30, RED, GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE };

#define COLOR_RESET   "\033[0m"
#define COLOR_BLACK   "\033[1;30m"
#define COLOR_RED     "\033[1;31m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_BLUE    "\033[1;34m"
#define COLOR_PURPLE  "\033[1;35m"
#define COLOR_CYAN    "\033[1;36m"
#define COLOR_WHITE   "\033[1;37m"

/*********************** Prototypes of Public Functions ***********************/

/* -------------------------- Services in console --------------------------- */

void Clear_Screen();
void gotoxy( unsigned char, unsigned char );
void textcolor( int );
void Get_Console_Size(unsigned char *x, unsigned char *y);
void Set_Console_Size( uint8_t x, uint8_t y );
void Cursor( int status );
void clearElement( const char *element[], unsigned char x, unsigned char y );

#endif /* CONIO_H */
