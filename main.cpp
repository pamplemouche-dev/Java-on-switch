#include <switch.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string>
#include <cstring>

// Appel au moteur traduit par le bot
extern "C" void start_minecraft_native_core();

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
        printf("\x1b[1;33m[Info]\x1b[0m Aucun dossier /switch/mods/ sur la SD.\n");
    }
}

int main(int argc, char* argv[]) {
    consoleInit(NULL);
    romfsInit();
    
    PadState pad;
    padInitializeDefault(&pad);

    printf("\x1b[1;32m--- Minecraft Switch Native Edition ---\x1b[0m\n");
    
    // Lancement du coeur traduit
    start_minecraft_native_core();

    // Scan des mods sur la SD (Accepte les mods sans les traduire)
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
