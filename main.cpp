#include <switch.h>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    // Initialisation console et système de fichiers (RomFS)
    consoleInit(NULL);
    romfsInit(); 
    
    printf("Démarrage de Java pour Minecraft...\n");

    // Configuration des manettes (Nouvelle API libnx)
    PadState pad;
    padInitializeDefault(&pad);

    JavaVM *jvm;       
    JNIEnv *env;       
    JavaVMInitArgs vm_args;
    JavaVMOption options[1];

    // On dit à Java de chercher Minecraft dans le RomFS
    options[0].optionString = (char*)"-Djava.class.path=romfs:/minecraft.jar";

    vm_args.version = JNI_VERSION_1_8;
    vm_args.nOptions = 1;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = JNI_FALSE;

    // Création de la machine virtuelle
    jint res = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
    
    if (res == JNI_OK) {
        printf("JVM lancée avec succès !\n");
        // On cherchera la classe Main de Minecraft ici plus tard
    } else {
        printf("Erreur JVM : %d\n", res);
    }

    printf("\nMaintenez (+) et (-) pour quitter.\n");

    while (appletMainLoop()) {
        padUpdate(&pad);
        u64 kDown = padGetButtonsDown(&pad);

        // Correction des noms de boutons selon ta capture 10:57
        if ((kDown & HidNpadButton_Plus) && (kDown & HidNpadButton_Minus)) break;

        consoleUpdate(NULL);
    }

    // Nettoyage avant de quitter
    if (res == JNI_OK) jvm->DestroyJavaVM();
    romfsExit();
    consoleExit(NULL);
    return 0;
}
