#include <switch.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    consoleInit(NULL);

    // C'est ici que ton NACP intervient pour identifier l'app
    printf("Démarrage de JavaSwitch...\n");
    printf("Chargement de la JRE Minecraft Java Edition...\n");

    // Simulation du lancement de la JVM (Java Virtual Machine)
    // Dans la version finale, on appelle libjvm.so
    
    while(appletMainLoop()) {
        hidScanInput();
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS) break; // Quitter le launcher

        consoleUpdate(NULL);
    }

    consoleExit(NULL);
    return 0;
}
