/* Ruler 1         2         3         4         5         6         7        */

/********************************** Headers ***********************************/

/* ------------------------ Inclusion of Std Headers ------------------------ */

#include <stdio.h>  // Due to printf
#include <stdint.h>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif




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


void Clear_Screen()
{
printf("\033[H\033[J");

} /* Clear_Screen */


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


/*FN****************************************************************************
*
*   void Cursor( int status );
*
*   Purpose: Show or hide cursor
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   Jun 15/21  J.C.Giraldo  Initial implementation
*
*******************************************************************************/


void Cursor( int status )
{
status ? printf( "\x1B[?25h" ) : printf( "\x1B[?25l" );

} /* Cursor */

/*FN****************************************************************************
*
*   void Set_Console_Size( uint8_t x, uint8_t y );
*
*   Purpose: Set console size
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

void Set_Console_Size( uint8_t x, uint8_t y )
{
printf( "\033[8;%d;%dt", y, x );

} /* Set_Console_Size */

/*FN****************************************************************************
*
*   void Get_Console_Size( uint8_t *x, uint8_t *y );
*
*   Purpose: Get console size
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

/* I made some changes to the function just for making it more compatible
with differents environments */

void Get_Console_Size(unsigned char *x, unsigned char *y)
{
#ifdef _WIN32
    // WINDOWS
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    *x = (unsigned char)(csbi.srWindow.Right - csbi.srWindow.Left + 1);
    *y = (unsigned char)(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);

#else
    // LINUX
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    *x = w.ws_col;
    *y = w.ws_row;
#endif
}


void clearElement( const char *element[], unsigned char x, unsigned char y )
{
for( int i = 0, j = 0; element[i][0] != '\0'; i++, j++ ) {
    gotoxy( x, y + j );
    int width = strlen( element[0] ) / 3;
    for( int spaces = 0; spaces < width; spaces++ )
        printf( " " );
}

} /* clearElement */