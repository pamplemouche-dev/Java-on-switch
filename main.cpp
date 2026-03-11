#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

// --- PROTECTION CONTRE L'ERREUR SYS/LOCK.H ---
#ifndef _SYS_LOCK_H_
#define _SYS_LOCK_H_
typedef int _LOCK_T;
typedef int _LOCK_RECURSIVE_T;
#endif

// Inclusion du header Switch depuis ton repo
#include "deps/include/switch.h" 

// --- DÉCLARATION UNIQUE DE LA JVM ---
extern "C" {
    typedef struct { void* reserved; } JNIEnv;
    typedef struct { JNIEnv* env; } JavaVM;
    int JNI_CreateJavaVM(JavaVM **jvm, void **env, void *args);
}

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
        printf("\x1b[1;31m[Info]\x1b[0m Dossier /switch/mods/ non detecte.\n");
    }
}

int main(int argc, char* argv[]) {
    // Initialisation standard libnx
    consoleInit(NULL);
    romfsInit();
    
    PadState pad;
    padInitializeDefault(&pad);

    printf("\x1b[1;32m--- Minecraft Switch (Titan Mini-JVM) ---\x1b[0m\n");

    JavaVM *jvm = NULL;
    void *env = NULL;

    // Appel de la fonction définie dans mini_jvm.cpp
    if (JNI_CreateJavaVM(&jvm, &env, NULL) == 0) {
        printf("Moteur Java initialise avec succes !\n");
    } else {
        printf("Erreur d'initialisation de la JVM.\n");
    }

    scanSDMods();

    printf("\n\x1b[1;32mAppuyez sur + pour quitter.\x1b[0m\n");

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
