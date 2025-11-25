#include <stdio.h>
#include <locale.h>
#include <stdlib.h> // para system("clear")
#include "screen.h"
#include "conio.h"  // si quieres usar Clear_Screen
#include "defalien.h"  // para usar squid, crab, octopus extern

// Calcula el "ancho visual" aproximado de una cadena UTF-8 en columnas.
// Cuenta solo el primer byte de cada carácter UTF-8 (ignora bytes de continuación).
static int get_display_width(const char *s) {
    int width = 0;
    unsigned char c;

    while ((c = (unsigned char)*s)) {
        if ((c & 0xC0) != 0x80) {
            // Byte inicial de un carácter UTF-8
            width++;
        }
        s++;
    }
    return width;
}
// ==========================================
// 1. ASSETS: PANTALLA DE TÍTULO
// ==========================================


char *space[] = {
    " \u2584\u2580\u2580\u2580\u2584 \u2588\u2580\u2580\u2580\u2588  \u2584\u2580\u2580\u2584  \u2584\u2580\u2580\u2580 \u2588\u2580\u2580\u2580", 
    " \u2580\u2580\u2580\u2584  \u2588\u2580\u2580\u2580\u2580 \u2588\u2580\u2580\u2580\u2588 \u2588     \u2588\u2580\u2580\u2580",
    " \u2584\u2584\u2584\u2580  \u2588     \u2588   \u2588  \u2580\u2584\u2584\u2584 \u2588\u2584\u2584\u2584",
    ""
};

char *invaders[] = {
    " \u2588 \u2588\u2580\u2584 \u2588 \u2588   \u2588  \u2584\u2580\u2580\u2584  \u2588\u2580\u2580\u2584  \u2588\u2580\u2580\u2580 \u2588\u2580\u2580\u2580\u2584  \u2584\u2580\u2580\u2580",
    " \u2588 \u2588 \u2580\u2584\u2588 \u2588   \u2588 \u2588\u2580\u2580\u2580\u2588  \u2588  \u2588  \u2588\u2580\u2580\u2580 \u2588\u2580\u2580\u2580\u2580  \u2580\u2580\u2580\u2584",
    " \u2588 \u2588   \u2588  \u2580\u2584\u2580  \u2588   \u2588  \u2588\u2584\u2584\u2580  \u2588\u2584\u2584\u2584 \u2588   \u2588 \u2584\u2584\u2584\u2580",
    ""
};

char *press_enter[] = {
    "\u2588\u2580\u2580\u2584 \u2588\u2580\u2580\u2584 \u2588\u2580\u2580\u2580 \u2584\u2580\u2580\u2580 \u2584\u2580\u2580\u2580   \u2588\u2580\u2580\u2580 \u2588\u2580\u2584\u2588 \u2580\u2588\u2580 \u2588\u2580\u2580\u2580 \u2588\u2580\u2580\u2584   \u2580\u2588\u2580 \u2584\u2580\u2580\u2584   \u2588\u2580\u2580\u2584 \u2588    \u2584\u2580\u2580\u2584 \u2588  \u2588",
    "\u2588\u2584\u2584\u2580 \u2588\u2584\u2584\u2580 \u2588\u2580\u2580\u2580 \u2580\u2580\u2580\u2584 \u2580\u2580\u2580\u2584   \u2588\u2580\u2580\u2580 \u2588 \u2580\u2588  \u2588  \u2588\u2580\u2580\u2580 \u2588\u2584\u2584\u2580    \u2588  \u2588  \u2588   \u2588\u2584\u2584\u2580 \u2588    \u2588\u2580\u2580\u2588  \u2580\u2584\u2580 ",
    "\u2588    \u2588  \u2588 \u2588\u2584\u2584\u2584 \u2584\u2584\u2584\u2580 \u2584\u2584\u2584\u2580   \u2588\u2584\u2584\u2584 \u2588  \u2588  \u2588  \u2588\u2584\u2584\u2584 \u2588  \u2588    \u2588  \u2580\u2584\u2584\u2580   \u2588    \u2588\u2584\u2584\u2584 \u2588  \u2588  \u2588 ",
    ""
};

char *score_header[] = {
    " \u2584\u2580\u2580 \u2584\u2580\u2580 \u2584\u2580\u2584 \u2588\u2580\u2584 \u2588\u2580\u2580   \u2584\u2580\u2584 \u2588\u2580\u2584 \u2588 \u2588 \u2584\u2580\u2584 \u2588\u2580\u2584 \u2584\u2580\u2580 \u2588\u2580\u2580   \u2580\u2588\u2580 \u2584\u2580\u2584 \u2588\u2580\u2584 \u2588   \u2588\u2580\u2580",
    " \u2580\u2580\u2584 \u2588   \u2588 \u2588 \u2588\u2580\u2584 \u2588\u2580\u2580   \u2588\u2580\u2588 \u2588 \u2588 \u2588 \u2588 \u2588\u2580\u2588 \u2588 \u2588 \u2588   \u2588\u2580\u2580    \u2588  \u2588\u2580\u2588 \u2588\u2580\u2584 \u2588   \u2588\u2580\u2580",
    " \u2584\u2584\u2580 \u2580\u2584\u2584 \u2580\u2584\u2580 \u2588 \u2588 \u2588\u2584\u2584   \u2588 \u2588 \u2588\u2584\u2580 \u2580\u2584\u2580 \u2588 \u2588 \u2588 \u2588 \u2580\u2584\u2584 \u2588\u2584\u2584    \u2588  \u2588 \u2588 \u2588\u2584\u2580 \u2588\u2584\u2584 \u2588\u2584\u2584",
    ""
};

// SPRITES
char *ufo[] =  {
    "\u259A\u2800\u2800\u259E\u259A\u2800\u2800\u259E",
    "\u2800\u2593\u259C\u259C\u259B\u259B\u2593\u2800",
    "\u2580\u2593\u259B\u259C\u259B\u259C\u2593\u2580",
    "\u2800\u259D\u2800\u2800\u2800\u2800\u2598\u2800",
    ""
};

// ==========================================
// 2. PANTALLA GAME OVER
// ==========================================

char *game_over_braille[] = {
    "\u2800\u2800\u2800\u2800\u2588\u2588\u2588\u2800\u2597\u2588\u2596\u2800\u2588\u2800\u2800\u2588\u2800\u2588\u2588\u2588\u2800\u2800\u2800\u2590\u2588\u258B\u2800\u2588\u2800\u2588\u2800\u2588\u2588\u2588\u2800\u2588\u2588\u2588\u2599\u2800\u2800\u2800\u2800",
    "\u2800\u2800\u2800\u2800\u2588\u2597\u2584\u2800\u259F\u2580\u2599\u2800\u2588\u2599\u259F\u2588\u2800\u2588\u2584\u2800\u2800\u2800\u2800\u2588\u2800\u2588\u2800\u2588\u2800\u2588\u2800\u2588\u2584\u2800\u2800\u2588\u2800\u2800\u2588\u2800\u2800\u2800\u2800",
    "\u2800\u2800\u2800\u2800\u2588\u259D\u2588\u2800\u2588\u2580\u2588\u2800\u2588\u2590\u258B\u2588\u2800\u2588\u2580\u2800\u2800\u2800\u2800\u2588\u2800\u2588\u2800\u2588\u2800\u2588\u2800\u2588\u2580\u2800\u2800\u2588\u2580\u2580\u2599\u2800\u2800\u2800\u2800",
    "\u2800\u2800\u2800\u2800\u2588\u2588\u2588\u2800\u2588\u2800\u2588\u2800\u2588\u2800\u2800\u2588\u2800\u2588\u2588\u2588\u2800\u2800\u2800\u2590\u2588\u258B\u2800\u259D\u2588\u2598\u2800\u2588\u2588\u2588\u2800\u2588\u2800\u2800\u2588\u2800\u2800\u2800\u2800",
    ""
};

char *press_play_gameover[] = {
    " \u2588\u2580\u2580\u2584 \u2588\u2580\u2580\u2584 \u2588\u2580\u2580\u2580 \u2588\u2580\u2580\u2580 \u2588\u2580\u2580\u2580   \u2588\u2580\u2580\u2580 \u2588\u2580\u2584\u2588 \u2580\u2588\u2580 \u2588\u2580\u2580\u2580 \u2588\u2580\u2580\u2584 ",
    " \u2588\u2584\u2584\u2580 \u2588\u2584\u2584\u2580 \u2588\u2580\u2580  \u2580\u2580\u2580\u2584 \u2580\u2580\u2580\u2584   \u2588\u2580\u2580  \u2588 \u2580\u2588  \u2588  \u2588\u2580\u2580  \u2588\u2584\u2584\u2580 ",
    " \u2588    \u2588  \u2588 \u2588\u2584\u2584\u2584 \u2584\u2584\u2584\u2580 \u2584\u2584\u2584\u2580   \u2588\u2584\u2584\u2584 \u2588  \u2588  \u2588  \u2588\u2584\u2584\u2584 \u2588\u2584\u2584\u2584 ",
    "",
    "       \u2580\u2588\u2580 \u2584\u2580\u2580\u2584   \u2588\u2580\u2580\u2584 \u2588    \u2584\u2580\u2580\u2584 \u2588   \u2588 ",
    "        \u2588  \u2588  \u2588   \u2588\u2584\u2584\u2580 \u2588    \u2588\u2580\u2580\u2588  \u2580\u2584\u2580  ",
    "        \u2588  \u2584\u2584\u2584\u2584  \u2588    \u2588\u2584\u2584\u2584 \u2588  \u2588   \u2588\u2584\u2584", 
    ""
};

char *or_text[] = {
    " \u2584\u2580\u2580\u2584 \u2588\u2580\u2580\u2584 ",
    " \u2588  \u2588 \u2588\u2584\u2584\u2580 ",
    " \u2580\u2584\u2584\u2580 \u2588\u2584\u2584\u2584 ",
    ""
};

char *press_quit[] = {
    " \u2588\u2580\u2580\u2584 \u2588\u2580\u2580\u2584 \u2588\u2580\u2580\u2580 \u2588\u2580\u2580\u2580 \u2588\u2580\u2580\u2580   \u2584\u2580\u2580\u2584 \u2588\u2580\u2584\u2588 \u2588   \u2588 ",
    " \u2588\u2584\u2584\u2580 \u2588\u2584\u2584\u2580 \u2588\u2580\u2580  \u2580\u2580\u2580\u2584 \u2580\u2580\u2580\u2584   \u2588\u2580\u2580\u2588 \u2588 \u2580\u2588  \u2580\u2584\u2580 ",
    " \u2588    \u2588  \u2588 \u2588\u2584\u2584\u2584 \u2584\u2584\u2584\u2580 \u2584\u2584\u2584\u2580   \u2588  \u2588 \u2588  \u2588   \u2588\u2584\u2584",
    "",
    "        \u2580\u2588\u2580 \u2584\u2580\u2580\u2584   \u2584\u2580\u2580\u2584 \u2588  \u2588 \u2580\u2588\u2580 \u2580\u2588\u2580 ",
    "         \u2588  \u2588  \u2588   \u2588  \u2588 \u2588  \u2588  \u2588   \u2588  ",
    "         \u2588  \u2584\u2584\u2584\u2584  \u2584\u2584\u2584\u2588 \u2580\u2584\u2584\u2580 \u2584\u2588\u2584  \u2588\u2584\u2584",
    ""
};

// ==========================================
// 3. FUNCIONES DE DIBUJADO
// ==========================================

// Imprime un bloque centrado horizontalmente usando el ancho de la consola
static void print_block_center(char *arr[], const char *color) {
    unsigned char W, H;
    Get_Console_Size(&W, &H);

    printf("%s", color);

    int i = 0;
    while (arr[i][0] != '\0') {
        int line_w = get_display_width(arr[i]);
        int margin = 0;

        if (W > line_w) {
            margin = (W - line_w) / 2;
        }

        for (int m = 0; m < margin; m++) printf(" ");
        printf("%s\n", arr[i]);
        i++;
    }

    printf(COLOR_RESET);
}


// Esta función ahora acepta 'char *text' (string normal) en vez de array
void print_score_row_pixel(char *sprite[], const char *color, const char *text, int margin) {
    // Calcular altura real del sprite
    int height = 0;
    while (sprite[height][0] != '\0') {
        height++;
    }

    int middle = height / 2;   // línea donde pondremos el texto

    for (int i = 0; i < height; i++) {
        // margen a la izquierda (para alinear todo este bloque)
        for (int m = 0; m < margin; m++) printf(" ");

        // sprite en color
        printf("%s%s", color, sprite[i]);

        printf("   "); // espacio entre alien y texto

        // imprimimos el texto en la línea central del sprite
        if (i == middle) {
            printf(COLOR_WHITE "%s", text);
        }

        printf("\n");
    }

    printf(COLOR_RESET "\n");
}

// ==========================================
// 4. PANTALLAS
// ==========================================

void mostrar_pantalla_titulo() {
    unsigned char W, H;
    Get_Console_Size(&W, &H);

    Clear_Screen();      // ahora usamos la función de conio.h

    printf("\n\n");      // pequeña separación desde la parte superior

    // TÍTULO
    print_block_center(space,   COLOR_GREEN);
    printf("\n");
    print_block_center(invaders, COLOR_GREEN);

    // 👉 Bajamos un poco más el PRESS ENTER (antes eran 2 saltos)
    printf("\n\n\n\n");

    // PRESS ENTER TO PLAY
    print_block_center(press_enter, COLOR_WHITE);

    printf("\n\n");
    // SCORE ADVANCE TABLE
    print_block_center(score_header, COLOR_WHITE);

    printf("\n\n");

    // Tabla de puntuaciones (aliens + texto)
    // Esto sigue alineado con un margen fijo. Si luego quieres,
    // también se puede centrar usando el ancho de consola.
    print_score_row_pixel(ufo,     COLOR_RED,     "= ? MYSTERY", 14);
    print_score_row_pixel(squid,   COLOR_GREEN,   "= 30 POINTS", 14);
    print_score_row_pixel(crab,    COLOR_CYAN,    "= 20 POINTS", 14);
    print_score_row_pixel(octopus, COLOR_PURPLE,  "= 10 POINTS", 14);

    printf("\n\n");
}


void mostrar_game_over() {

    unsigned char W, H;
    Get_Console_Size(&W, &H);
    
    Clear_Screen();  // si prefieres que borre dentro de la función
    printf("\n\n");
    print_block_center(game_over_braille, COLOR_YELLOW);

    printf("\n\n");
    print_block_center(press_play_gameover, COLOR_GREEN);

    printf("\n");
    print_block_center(or_text, COLOR_PURPLE);

    printf("\n");
    print_block_center(press_quit, COLOR_CYAN);

    printf("\n\n");
}
