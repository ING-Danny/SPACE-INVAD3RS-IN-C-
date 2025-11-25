#include "numeros.h"
#include "alien.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// ------------------- Numeros como sprites -------------------
char *numero0[] = {
    " ██ ",
    "█  █",
    "█  █",
    " ██ ",
    ""
};

char *numero1[] = {
    "  █ ",
    " ██ ",
    "  █ ",
    "████",
    ""
};

char *numero2[] = {
    "███ ",
    "   █",
    " ██ ",
    "████",
    ""
};

char *numero3[] = {
    "███ ",
    "  ██",
    "   █",
    "███ ",
    ""
};

char *numero4[] = {
    "█ ██",
    "█  █",
    "████",
    "   █",
    ""
};

char *numero5[] = {
    "████",
    "█   ",
    " ███",
    "   █",
    ""
};

char *numero6[] = {
    " ██ ",
    "█   ",
    "████",
    " ███",
    ""
};

char *numero7[] = {
    "████",
    "   █",
    "  █ ",
    " █  ",
    ""
};

char *numero8[] = {
    " ██ ",
    "█  █",
    " ██ ",
    "█  █",
    ""
};

char *numero9[] = {
    " ███",
    "█  █",
    " ███",
    "   █",
    ""
};

// ------------------- Función de creación dinámica -------------------
ALIEN_T *CreateNumber(int n, int color, unsigned char x, unsigned char y) {
    ALIEN_T *num = New_alien();
    switch (n) {
        case 0: Set_Aspect(num, &numero0); break;
        case 1: Set_Aspect(num, &numero1); break;
        case 2: Set_Aspect(num, &numero2); break;
        case 3: Set_Aspect(num, &numero3); break;
        case 4: Set_Aspect(num, &numero4); break;
        case 5: Set_Aspect(num, &numero5); break;
        case 6: Set_Aspect(num, &numero6); break;
        case 7: Set_Aspect(num, &numero7); break;
        case 8: Set_Aspect(num, &numero8); break;
        case 9: Set_Aspect(num, &numero9); break;
        default: Set_Aspect(num, &numero0); break;
    }

    Set_alien_color(num, color);
    SetAlienLocation(num, x, y);
    DrawAlien(num);

    return num;
}
