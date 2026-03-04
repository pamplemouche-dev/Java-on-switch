#include <switch.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// On redirige les appels GLIBC manquants vers les fonctions Switch
extern "C" {
    void __longjmp_chk() { exit(0); }
    void __stack_chk_fail() { exit(0); }
    
    // Minecraft demande souvent ces fonctions pour la gestion des fichiers
    FILE* fopen64(const char* filename, const char* mode) {
        return fopen(filename, mode);
    }
}
