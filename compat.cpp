#include <switch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

extern "C" {
    // Gestion de la pile
    void __stack_chk_fail() { exit(0); }
    void __assert_fail(const char * a, const char * b, unsigned int c, const char * d) { exit(0); }
    
    // Fonctions mémoires (Fix de l'erreur memchr de la capture 13:41)
    void* __rawmemchr(const void* s, int c) { return (void*)memchr(s, c, 1024*1024); }

    // Redirections Fichiers 64-bit pour Java/Minecraft
    FILE* fopen64(const char* f, const char* m) { return fopen(f, m); }
    int fseeko64(FILE* s, off_t o, int w) { return fseeko(s, o, w); }
    off_t ftello64(FILE* s) { return ftello(s); }

    // Stubs pour les signaux (On remplace sigset_t par void* pour éviter l'erreur de syntaxe)
    int sigemptyset(void* set) { return 0; }
    int sigfillset(void* set) { return 0; }
    int sigaddset(void* set, int signo) { return 0; }
    int sigaction(int a, const void* b, void* c) { return 0; }
}
