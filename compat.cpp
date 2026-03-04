#define _GNU_SOURCE
#include <switch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// On empêche les conflits avec les types système
#define sigset_t void
#define sigaction void

extern "C" {
    // 1. Sécurité et Pile
    void __stack_chk_fail() { exit(0); }
    void __assert_fail(const char* a, const char* b, unsigned int c, const char* d) { exit(0); }
    
    // 2. Mémoire (Correction de l'erreur memchr 13:41)
    void* __rawmemchr(const void* s, int c) { return (void*)memchr(s, c, 1024*1024); }

    // 3. Fichiers 64-bit (Crucial pour les gros .jar de Forge/Mekanism)
    FILE* fopen64(const char* f, const char* m) { return fopen(f, m); }
    int fseeko64(FILE* s, off_t o, int w) { return fseeko(s, o, w); }
    off_t ftello64(FILE* s) { return ftello(s); }
    int fgetpos64(FILE* s, fpos_t* p) { return fgetpos(s, p); }
    int fsetpos64(FILE* s, const fpos_t* p) { return fsetpos(s, p); }

    // 4. Stubs Signaux (On utilise int pour éviter les erreurs de type 13:44)
    int sigemptyset(void* set) { return 0; }
    int sigfillset(void* set) { return 0; }
    int sigaddset(void* set, int signo) { return 0; }
    int sigaction(int a, const void* b, void* c) { return 0; }
    
    // 5. Autres fonctions GLIBC manquantes vues dans tes logs
    int __fxstat64(int ver, int fd, void* buf) { return -1; }
    int __lxstat64(int ver, const char* path, void* buf) { return -1; }
    int __xstat64(int ver, const char* path, void* buf) { return -1; }
}
