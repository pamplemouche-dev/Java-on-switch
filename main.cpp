#include <switch.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <cstring>

// Cette fonction est générée dynamiquement par le bot dans minecraft_server_native.cpp
extern "C" void start_minecraft_native_core();

// Fonction pour scanner les mods sur la carte SD
void scanSDMods() {
    printf("\x1b[1;34m[SD Card]\x1b[0m Recherche de mods dans sdmc:/switch/mods/...\n");
    DIR* dir = opendir("sdmc:/switch/mods/");
    if (dir) {
        struct dirent* ent;
        while ((ent = readdir(dir)) != NULL) {
            if (strstr(ent->d_name, ".jar")) {
                printf("  -> Mod detecte : %s\n", ent->d_name);
            }
        }
        closedir(dir);
    } else {
        printf("\x1b[1;31m[Erreur]\x1b[0m Dossier /switch/mods/ introuvable sur la SD.\n");
    }
}

int main(int argc, char* argv[]) {
    consoleInit(NULL);
    romfsInit();
    
    PadState pad;
    padInitializeDefault(&pad);

    printf("\x1b[1;32m--- Minecraft Switch Native Edition ---\x1b[0m\n");
    printf("Statut : Moteur traduit par Bot AOT\n\n");

    // 1. Lancer le coeur du jeu (déjà traduit en C++)
    printf("Initialisation du coeur de Minecraft...\n");
    start_minecraft_native_core();

    // 2. Scanner les mods sur la SD
    scanSDMods();

    printf("\n\x1b[1;32mPret ! Appuyez sur + pour quitter.\x1b[0m\n");

    while (appletMainLoop()) {
        padUpdate(&pad);
        u64 kDown = padGetButtonsDown(&pad);

        if (kDown & HidNpadButton_Plus) break;

        consoleUpdate(NULL);
    }

    romfsExit();
    consoleExit(NULL);
    return 0;
}
