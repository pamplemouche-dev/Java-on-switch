#include <switch.h>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    consoleInit(NULL);
    printf("Démarrage de Java pour Minecraft...\n");

    JavaVM *jvm;       
    JNIEnv *env;       
    JavaVMInitArgs vm_args;
    JavaVMOption options[2];

    // Chemin vers ton JAR dans le romfs de la Switch
    options[0].optionString = (char*)"-Djava.class.path=romfs:/minecraft.jar";
    options[1].optionString = (char*)"-Xmx256M"; // Allocation RAM

    vm_args.version = JNI_VERSION_1_8;
    vm_args.nOptions = 2;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = JNI_FALSE;

    // Création de la machine virtuelle
    jint res = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
    if (res != JNI_OK) {
        printf("Erreur : Impossible de créer la JVM (%d)\n", res);
    } else {
        printf("JVM lancée avec succès !\n");
        
        // Ici, on cherchera la classe Main de Minecraft
        jclass cls = env->FindClass("net/minecraft/client/main/Main");
        if (cls == NULL) {
            printf("Erreur : Classe Main introuvable.\n");
        }
    }

    printf("\nAppuyez sur (+) pour quitter.\n");
    while (appletMainLoop()) {
        hidScanInput();
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
        if (kDown & KEY_PLUS) break;
        consoleUpdate(NULL);
    }

    if (res == JNI_OK) jvm->DestroyJavaVM();
    consoleExit(NULL);
    return 0;
}
