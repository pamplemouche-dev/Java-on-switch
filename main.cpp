#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

// --- TRICK POUR BYPASSER SYS/LOCK.H ---
// On définit les gardes et les types avant d'inclure switch.h
#ifndef _SYS_LOCK_H_
#define _SYS_LOCK_H_
#define _SYS_REENT_H_ // On bloque aussi reent.h qui pose souvent souci
typedef int _LOCK_T;
typedef int _LOCK_RECURSIVE_T;
#endif

// On inclut switch.h APRÈS les définitions ci-dessus
#include "deps/include/switch.h" 

extern "C" {
    typedef struct { void* reserved; } JNIEnv;
    typedef struct { JNIEnv* env; } JavaVM;
    int JNI_CreateJavaVM(JavaVM **jvm, void **env, void *args);
}

int main(int argc, char* argv[]) {
    consoleInit(NULL);
    printf("\x1b[1;32m--- Titan-JVM Native ---\x1b[0m\n");

    JavaVM *jvm = NULL;
    void *env = NULL;

    if (JNI_CreateJavaVM(&jvm, &env, NULL) == 0) {
        printf("Mini-JVM OK.\n");
    }

    while (appletMainLoop()) {
        consoleUpdate(NULL);
    }

    consoleExit(NULL);
    return 0;
}
