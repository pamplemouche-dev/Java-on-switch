#ifndef JNI_TITAN_H
#define JNI_TITAN_H

#include <stdint.h>

extern "C" {
    // Définitions minimales pour tromper le compilateur et simuler Java
    typedef struct { void* reserved0; void* reserved1; void* reserved2; } JNIEnv;
    typedef struct { JNIEnv* env; } JavaVM;

    // Déclaration de la fonction que tu as dans mini_jvm.cpp
    int JNI_CreateJavaVM(JavaVM **p_vm, void **p_env, void *vm_args);
}

#endif
