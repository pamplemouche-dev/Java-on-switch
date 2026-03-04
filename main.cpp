#include <switch.h>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    // Initialisation graphique de base
    consoleInit(NULL);
    printf("Démarrage de Java pour Minecraft...\n");

    // Nouvelle API Hid pour les manettes
    PadState pad;
    padInitializeDefault(&pad);

    JavaVM *jvm;       
    JNIEnv *env;       
    JavaVMInitArgs vm_args;
    JavaVMOption options[1];

    // On prépare le chemin pour le JAR de Minecraft
    options[0].optionString = (char*)"-Djava.class.path=romfs:/minecraft.jar";

    vm_args.version = JNI_VERSION_1_8;
    vm_args.nOptions = 1;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = JNI_FALSE;

    // Tentative de création de la JVM
    jint res = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
    
    if (res == JNI_OK) {
        printf("JVM lancée ! Recherche de Minecraft...\n");
        // Simulation de recherche de classe
        jclass cls = env->FindClass("net/minecraft/client/main/Main");
        if (cls == NULL) printf("Note: minecraft.jar absent (normal pour le test).\n");
    } else {
        printf("Erreur JVM: %d\n", res);
    }

    printf("\nMaintenez (+) et (-) pour quitter.\n");

    while (appletMainLoop()) {
        // Nouvelle façon de lire les touches
        padUpdate(&pad);
        u64 kDown = padGetButtonsDown(&pad);

        // Quitter si on appuie sur + et -
        if ((kDown & HydButtons_Plus) && (kDown & HydButtons_Minus)) break;

        consoleUpdate(NULL);
    }

    if (res == JNI_OK) jvm->DestroyJavaVM();
    consoleExit(NULL);
    return 0;
}
