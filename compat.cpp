#include <switch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// On définit des "leurres" pour satisfaire le linker de libjvm.so
extern "C" {
    void __stack_chk_fail() { exit(0); }
    void __assert_fail(const char* a, const char* b, unsigned int c, const char* d) { exit(0); }
    
    // Correction memchr (capture 13:41)
    void* __rawmemchr(const void* s, int c) { return (void*)memchr(s, c, 1024*1024); }

    // Support fichiers 64-bit pour les JAR lourds (Mekanism/Create)
    FILE* fopen64(const char* f, const char* m) { return fopen(f, m); }
    int fseeko64(FILE* s, off_t o, int w) { return fseeko(s, o, w); }
    off_t ftello64(FILE* s) { return ftello(s); }

    // Stubs pour les signaux Linux (on utilise void* pour éviter les conflits de types)
    int sigemptyset(void* set) { return 0; }
    int sigfillset(void* set) { return 0; }
    int sigaddset(void* set, int signo) { return 0; }
    
    // On renomme pour éviter le conflit de la capture 13:44
    int sigaction(int sig, const void* act, void* oact) { return 0; }
}
