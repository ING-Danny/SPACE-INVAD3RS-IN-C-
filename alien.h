/* Ruler 1         2         3         4         5         6         7        */

#ifndef	ALIEN_H
#define ALIEN_H

/******************** Declaration of Class with Attributes ********************/

typedef struct ALIEN_T ALIEN_T;



/************************ Prototypes of Public Methods ************************/

/* ------------------------ Constructor & Destructor ------------------------ */

ALIEN_T * New_alien();
int       Free_alien( ALIEN_T * );

/* ------------------------ Setting Alien Attributes ------------------------ */

ALIEN_T *   Set_Aspect( ALIEN_T *, char *(*)[] );
ALIEN_T *   Set_alien_color( ALIEN_T *, int );
ALIEN_T * SetAlienLocation( ALIEN_T *, unsigned char, unsigned char );

/* ------------------------ Performing Alien Actions ------------------------ */

void DrawAlien( ALIEN_T * );
#endif /* ALIEN_H */
