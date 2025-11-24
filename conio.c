/* Ruler 1         2         3         4         5         6         7        */

/********************************** Headers ***********************************/

/* ------------------------ Inclusion of Std Headers ------------------------ */

#include <stdio.h>  // Due to printf




/************************ Definition of Public Methods ************************/

/* -------------------------- Services in console --------------------------- */

/*FN****************************************************************************
*
*   void textcolor( int color );
*
*   Purpose: Change the color of drawing text
*
*   Plan:    Simple function that does not need a plan description
*
*   Register of Revisions:
*
*   DATE         RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   Oct 31/2020  J.C.Giraldo  Documentation
*
*******************************************************************************/

void textcolor( int color )
{
printf( "\033[1;%dm", color );

} /* textcolor */



/*FN****************************************************************************
*
*   void clrscr();
*
*   Purpose: Clear screen with escape ANSI sequence
*
*   Plan:    Simple function that does not need a plan description
*
*   Register of Revisions:
*
*   DATE         RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   Oct 31/2020  J.C.Giraldo  Documentation
*
*******************************************************************************/

void clrscr()
{
printf( "\033[H\033[J" );

} /* clrscr */



/*FN****************************************************************************
*
*   void gotoxy( unsigned char x, unsigned char y );
*
*   Purpose: Position cursor
*
*   Plan:    Simple function that does not need a plan description
*
*   Register of Revisions:
*
*   DATE         RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   Oct 31/2020  J.C.Giraldo  Documentation
*
*******************************************************************************/

void gotoxy( unsigned char x, unsigned char y )
{
printf( "\033[%d;%df", y, x );

} /* gotoxy */
