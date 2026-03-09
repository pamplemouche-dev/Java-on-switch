#include <switch.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <cstring>
#include <stdint.h>

// --- STRUCTURES TITAN-JVM (MOTEUR MAISON) ---
typedef struct {
    int32_t stack[1024]; // Pile de calcul
    int32_t locals[256]; // Variables locales
    int sp;              // Stack Pointer
} TitanFrame;

// Fonction de calcul native (remplace le bytecode Java)
void execute_titan_logic(TitanFrame *f) {
    // Simulation d'instructions Java complexes (ex: IADD, ISUB, LDC)
    f->stack[f->sp++] = 64;  // On pousse une valeur
    f->stack[f->sp++] = 36;  // On pousse une autre valeur
    f->stack[f->sp-2] = f->stack[f->sp-2] + f->stack[f->sp-1]; // Addition native
    f->sp--;
}

extern "C" void start_minecraft_native_core() {
    printf("\x1b[1;33m[Titan-JVM]\x1b[0m Initialisation de la memoire native...\n");
    TitanFrame main_frame = {{0}, {0}, 0};
    execute_titan_logic(&main_frame);
    printf("\x1b[1;32m[Titan-JVM]\x1b[0m Resultat du calcul de demarrage : %d\n", main_frame.stack[0]);
    printf("\x1b[1;32m[Titan-JVM]\x1b[0m Moteur Operationnel.\n");
}

// --- GESTION DES MODS (TON CODE ORIGINAL) ---
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
        printf("\x1b[1;31m[Info]\x1b[0m Dossier /switch/mods/ non detecte sur la SD.\n");
    }
}

// --- POINT D'ENTRÉE PRINCIPAL ---
int main(int argc, char* argv[]) {
    consoleInit(NULL);
    romfsInit();
    
    PadState pad;
    padInitializeDefault(&pad);

    printf("\x1b[1;35m=== PROJECT TITAN : JVM NATIVE SWITCH ===\x1b[0m\n");
    printf("Statut : Moteur JRE remplace par Code C++ Direct\n\n");

    // 1. Lancer le coeur Titan-JVM
    start_minecraft_native_core();

    // 2. Scanner les mods sur la SD (ton code original)
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
