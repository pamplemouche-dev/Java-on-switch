#include <stdio.h>
#include <stdlib.h>

extern "C" {
    // Une seule définition ici
    typedef struct { void* reserved; } JNIEnv;
    typedef struct { JNIEnv* env; } JavaVM;

    int JNI_CreateJavaVM(JavaVM **jvm, void **env, void *args) {
        printf("[Mini-JVM] Allocation memoire...\n");
        *jvm = (JavaVM*)malloc(sizeof(JavaVM));
        *env = (void*)malloc(sizeof(JNIEnv));
        
        if (*jvm == NULL || *env == NULL) return -1;
        
        printf("[Mini-JVM] Moteur Titan pret.\n");
        return 0; 
    }
}
