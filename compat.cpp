#include <switch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern "C" {
    // Symboles GLIBC manquants (vu sur capture 06:45)
    void __stack_chk_fail() { exit(0); }
    int fileno(FILE *stream) { return 1; }
    int getpriority(int which, int who) { return 0; }
    void* dladdr(const void *addr, void *info) { return NULL; }
    char* strncpy(char* dest, const char* src, size_t n) { return (char*)memcpy(dest, src, n); }
    int _exit(int status) { exit(status); return 0; }
    
    // Gestion réseau/système basique
    int gethostname(char *name, size_t len) { snprintf(name, len, "switch"); return 0; }
    void flockfile(FILE *filehandle) {}
    void funlockfile(FILE *filehandle) {}

    // Fichiers 64-bit
    FILE* fopen64(const char* f, const char* m) { return fopen(f, m); }
    int fseeko64(FILE* s, off_t o, int w) { return fseeko(s, o, w); }
    off_t ftello64(FILE* s) { return ftello(s); }

    // Stubs Signaux
    int sigemptyset(void* set) { return 0; }
    int sigfillset(void* set) { return 0; }
    int sigaddset(void* set, int signo) { return 0; }
    int sigaction(int sig, const void* act, void* oact) { return 0; }
}
