#include <switch.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <cstring>

// --- LIAISON AVEC LE BOT ---
// Cette fonction sera créée par translator.py et injectée dans minecraft_server_native.cpp
extern "C" void start_minecraft_native_core();

int main(int argc, char* argv[]) {
    consoleInit(NULL);
    romfsInit();
    
    PadState pad;
    padInitializeDefault(&pad);

    printf("\x1b[1;32m--- Minecraft Switch AOT Launcher ---\x1b[0m\n");
    printf("Mode : Natif (AOT) + Mods SD\n\n");

    // 1. DÉMARRAGE DU CŒUR TRADUIT
    // C'est instantané car le Bot GitHub a déjà fait le travail
    printf("Chargement du moteur traduit...\n");
    start_minecraft_native_core();

    // 2. SCAN DES MODS SUR LA CARTE SD
    // On cherche dans sdmc:/switch/mods/ pour ne pas alourdir le NRO
    printf("Recherche de mods sur SD (sdmc:/switch/mods/)... \n");
    DIR* dir = opendir("sdmc:/switch/mods/");
    if (dir) {
        struct dirent* ent;
        int modCount = 0;
        while ((ent = readdir(dir)) != NULL) {
            if (strstr(ent->d_name, ".jar")) {
                printf(" - \x1b[1;34mMod detecte\x1b[0m : %s\n", ent->d_name);
                modCount++;
                // Ici, on passera plus tard le chemin au moteur pour le chargement dynamique
            }
        }
        closedir(dir);
        if(modCount == 0) printf("Aucun mod trouve.\n");
    } else {
        printf("\x1b[1;33mDossier /switch/mods/ absent sur la SD.\x1b[0m\n");
    }

    printf("\n\x1b[1;32mPret ! Appuyez sur + pour quitter.\x1b[0m\n");

    while (appletMainLoop()) {
        padUpdate(&pad);
        u64 kDown = padGetButtonsDown(&pad);

        // Sortie avec le bouton Plus
        if (kDown & HidNpadButton_Plus) break;

        consoleUpdate(NULL);
    }

    romfsExit();
    consoleExit(NULL);
    return 0;
}
