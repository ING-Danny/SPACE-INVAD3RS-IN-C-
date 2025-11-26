#include "alien.h"
#include "conio.h"
#include "defalien.h"
#include "numeros.h"
#include "screen.h"
#include "dibujaraliens.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <locale.h>
#include <unistd.h>



enum { SQUID_ROW, CRAB_ROW, OCTOPUS_ROW };

int main() {
    GameObjects *game = InitGameObjects();
    RunGameLoop(game);
    FreeGameObjects(game);
    return 0;

    return 0;
}

