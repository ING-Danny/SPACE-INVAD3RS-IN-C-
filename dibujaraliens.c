#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // usleep
#include <termios.h>
#include <fcntl.h>
#include "alien.h"
#include "defalien.h"
#include "screen.h"
#include "conio.h"
#include "numeros.h"



// Configuración
#define N_ALIENS 12
#define N_SHIELDS 3
#define SPRITE_SPACE 3
#define SPRITE_WIDTH 8

typedef struct {
    ALIEN_T **aliens;
    int num_aliens;
    ALIEN_T *shields[N_SHIELDS];
    ALIEN_T *cannon;
    ALIEN_T *saucer;
} GameObjects;

// ---------------------- FUNCIONES PORTABLES ----------------------
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF){
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

int getch(void){
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

// ---------------------- MOVER SAUCER ----------------------
void MoveSaucer(ALIEN_T *saucer){
    // Por ahora permanece fijo
}

// Borra un alien de la pantalla
void ClearAlien(ALIEN_T *alien){
    if(!alien) return;
    for(int i=0;i<alien->height;i++){
        gotoxy(alien->posx, alien->posy + i);
        for(int j=0;j<alien->width;j++) printf(" ");
    }
}

// ---------------------- INICIALIZAR OBJETOS ----------------------
GameObjects *InitGameObjects(void){
    unsigned char W,H;
    Get_Console_Size(&W,&H);

    GameObjects *obj = (GameObjects *)malloc(sizeof(GameObjects));
    obj->num_aliens = N_ALIENS*3;
    obj->aliens = (ALIEN_T **)malloc(sizeof(ALIEN_T*)*obj->num_aliens);

    int idx=0;
    int startX = (W - (N_ALIENS*(SPRITE_WIDTH+SPRITE_SPACE)))/2;
    int y_squid = 5;

    // Plantillas de aliens
    ALIEN_T *sq = New_alien(); Set_Aspect(sq,&squid);
    ALIEN_T *cr = New_alien(); Set_Aspect(cr,&crab);
    ALIEN_T *oc = New_alien(); Set_Aspect(oc,&octopus);

    // Dibujar SQUIDS
    for(int i=0;i<N_ALIENS;i++){
        ALIEN_T *a = New_alien(); *a=*sq;
        SetAlienLocation(a, startX + i*(SPRITE_WIDTH+SPRITE_SPACE), y_squid);
        Set_alien_color(a, PURPLE);
        obj->aliens[idx++] = a;
    }
    int y_crab = y_squid + sq->height + 2;
    for(int i=0;i<N_ALIENS;i++){
        ALIEN_T *a = New_alien(); *a=*cr;
        SetAlienLocation(a, startX + i*(SPRITE_WIDTH+SPRITE_SPACE), y_crab);
        Set_alien_color(a, BLUE);
        obj->aliens[idx++] = a;
    }
    int y_oct = y_crab + cr->height + 2;
    for(int i=0;i<N_ALIENS;i++){
        ALIEN_T *a = New_alien(); *a=*oc;
        SetAlienLocation(a, startX + i*(SPRITE_WIDTH+SPRITE_SPACE), y_oct);
        Set_alien_color(a, CYAN);
        obj->aliens[idx++] = a;
    }

    Free_alien(sq); Free_alien(cr); Free_alien(oc);

    // ---------------------- SHIELDS ----------------------
    int shieldsY = y_oct + oc->height + 6;
    int shieldW = 7;
    int totalShieldWidth = N_SHIELDS * shieldW;
    int spaceBetweenShields = (W - totalShieldWidth) / (N_SHIELDS + 1);
    for(int i=0;i<N_SHIELDS;i++){
        obj->shields[i] = New_alien();
        Set_Aspect(obj->shields[i], &shield);
        int shieldX = spaceBetweenShields*(i+1) + shieldW*i;
        SetAlienLocation(obj->shields[i], shieldX, shieldsY);
        Set_alien_color(obj->shields[i], GREEN);
    }

    // ---------------------- CANNON ----------------------
    obj->cannon = New_alien();
    Set_Aspect(obj->cannon, &cannon);
    int cannonX = (W - obj->cannon->width)/2;
    int cannonY = H - obj->cannon->height - 2;
    SetAlienLocation(obj->cannon, cannonX, cannonY);
    Set_alien_color(obj->cannon, WHITE);

    // ---------------------- SAUCER ----------------------
    obj->saucer = New_alien();
    Set_Aspect(obj->saucer, &saucer);
    int saucerX = (W - obj->saucer->width)/2;
    int saucerY = 1;
    SetAlienLocation(obj->saucer, saucerX, saucerY);
    Set_alien_color(obj->saucer, RED);

    return obj;
}

// ---------------------- LOOP DEL JUEGO ----------------------
void RunGameLoop(GameObjects *obj){
    if(!obj) return;
    mostrar_pantalla_titulo();

    // Esperar Enter
    int ch;
    printf("\n\nPresiona ENTER para empezar...");
    while(1){
        if(kbhit()){
            ch = getch();
            if(ch == '\r' || ch == '\n') break;
        }
        usleep(10000);
    }

    Clear_Screen();

    unsigned char W,H;
    Get_Console_Size(&W,&H);

    int alien_dx = 1;

    while(1){
        usleep(100000); // 0.1s/frame
        Get_Console_Size(&W,&H);

        // ---------------------- MOVER BLOQUE DE ALIENS ----------------------
        int bloque_dx = alien_dx;
        for(int i=0;i<obj->num_aliens;i++){
            if(obj->aliens[i]->posx + obj->aliens[i]->width >= W-1) bloque_dx = -1;
            if(obj->aliens[i]->posx <= 0) bloque_dx = 1;
        }
        for(int i=0;i<obj->num_aliens;i++){
            ClearAlien(obj->aliens[i]);
            obj->aliens[i]->posx += bloque_dx;
            DrawAlien(obj->aliens[i]);
        }
        alien_dx = bloque_dx;

        // ---------------------- CONTROL DEL CANNON ----------------------
        if(kbhit()){
            ch = getch();
            ClearAlien(obj->cannon);
            if(ch == 'a' || ch == 'A'){
                if(obj->cannon->posx > 0)
                    obj->cannon->posx -= 2;
            }
            if(ch == 'd' || ch == 'D'){
                if(obj->cannon->posx + obj->cannon->width < W)
                    obj->cannon->posx += 2;
            }
        }

        // ---------------------- DIBUJAR SHIELDS ----------------------
        for(int i=0;i<N_SHIELDS;i++) DrawAlien(obj->shields[i]);

        // ---------------------- DIBUJAR CANNON ----------------------
        DrawAlien(obj->cannon);

        // ---------------------- DIBUJAR SAUCER ----------------------
        ClearAlien(obj->saucer);
        MoveSaucer(obj->saucer);
        DrawAlien(obj->saucer);

        // ---------------------- DIBUJAR V I D A S (CORAZONES) ----------------------
        ALIEN_T *vida = New_alien();
        Set_Aspect(vida, &corazon);

        int numVidas = 3;
        int vidaSpace = 1;
        int vidaW = vida->width;
        int vidaY = obj->saucer->posy;
        int vidaX = W - (numVidas * vidaW + (numVidas - 1) * vidaSpace);

        for (int i = 0; i < numVidas; i++) {
            SetAlienLocation(vida, vidaX + i * (vidaW + vidaSpace), vidaY);
            Set_alien_color(vida, RED);
            DrawAlien(vida);
        }
        Free_alien(vida);

        // ---------------------- DIBUJAR SCORE INICIAL ----------------------
        ALIEN_T *num_izq = CreateNumber(0, RED, 5, obj->saucer->posy);
        DrawAlien(num_izq);
        Free_alien(num_izq);
    }

    mostrar_game_over();
}

// ---------------------- LIBERAR MEMORIA ----------------------
void FreeGameObjects(GameObjects *obj){
    if(!obj) return;
    for(int i=0;i<obj->num_aliens;i++) Free_alien(obj->aliens[i]);
    free(obj->aliens);
    for(int i=0;i<N_SHIELDS;i++) Free_alien(obj->shields[i]);
    Free_alien(obj->cannon);
    Free_alien(obj->saucer);
    free(obj);
}