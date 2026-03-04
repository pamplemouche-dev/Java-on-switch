#include <switch.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

extern "C" {
    // Gestion de la pile et erreurs fatales
    void __stack_chk_fail() { exit(0); }
    void __assert_fail(const char * assertion, const char * file, unsigned int line, const char * function) { exit(0); }
    void __chk_fail() { exit(0); }

    // Redirections Fichiers 64-bit (indispensable pour Minecraft)
    FILE* fopen64(const char* filename, const char* mode) { return fopen(filename, mode); }
    int fseeko64(FILE* stream, off_t offset, int whence) { return fseeko(stream, offset, whence); }
    off_t ftello64(FILE* stream) { return ftello(stream); }
    int fgetpos64(FILE* stream, fpos_t* pos) { return fgetpos(stream, pos); }
    int fsetpos64(FILE* stream, const fpos_t* pos) { return fsetpos(stream, pos); }

    // Fonctions mémoire et divers
    void* __rawmemchr(const void* s, int c) { return (void*)memchr(s, c, 0xFFFFFFFF); }
    
    // Stub pour les signaux (la Switch ne les gère pas comme Linux)
    int sigemptyset(sigset_t *set) { return 0; }
    int sigaction(int sig, const struct sigaction *act, struct sigaction *oact) { return 0; }
    int sigfillset(sigset_t *set) { return 0; }
    int sigaddset(sigset_t *set, int signo) { return 0; }
}
