#include <stdio.h>
#include <stdlib.h>

extern "C" {
    typedef struct { void* reserved; } JNIEnv;
    typedef struct { JNIEnv* env; } JavaVM;

    // Cette fonction est celle appelée par le main.cpp
    int JNI_CreateJavaVM(JavaVM **jvm, void **env, void *args) {
        printf("[Mini-JVM] Allocation de la pile Titan...\n");
        
        *jvm = (JavaVM*)malloc(sizeof(JavaVM));
        *env = (void*)malloc(sizeof(JNIEnv));
        
        if (*jvm == NULL || *env == NULL) return -1;

        printf("[Mini-JVM] Moteur pret pour executer le bytecode.\n");
        return 0; 
    }
}extern "C" {
    typedef struct { void* functions; } JNIEnv;
    typedef struct { JNIEnv* env; } JavaVM;

    int JNI_CreateJavaVM(JavaVM **jvm, void **env, void *args) {
        printf("\x1b[1;33m[Titan-JVM]\x1b[0m Initialisation du moteur de calcul haute performance...\n");
        *jvm = (JavaVM*)malloc(sizeof(JavaVM));
        *env = (void*)malloc(sizeof(JNIEnv));
        printf("\x1b[1;32m[Titan-JVM]\x1b[0m Moteur pret. Pret a injecter Minecraft.\n");
        return 0; 
    }
}
