#include <switch.h>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string>
#include <vector>

// Fonction pour scanner les mods et créer le classpath
std::string buildClasspath() {
    std::string cp = "-Djava.class.path=";
    DIR* dir = opendir("romfs:/mods");
    struct dirent* ent;
    bool first = true;

    if (dir) {
        while ((ent = readdir(dir)) != NULL) {
            // On vérifie si c'est un fichier .jar
            if (strstr(ent->d_name, ".jar")) {
                if (!first) cp += ":";
                cp += "romfs:/mods/";
                cp += ent->d_name;
                first = false;
                printf("Mod trouvé : %s\n", ent->d_name);
            }
        }
        closedir(dir);
    } else {
        printf("Erreur : Impossible d'ouvrir romfs:/mods\n");
    }
    return cp;
}

int main(int argc, char* argv[]) {
    // 1. Initialisation de la Switch
    consoleInit(NULL);
    romfsInit();
    
    // Initialisation des manettes (API PadState pour libnx moderne)
    PadState pad;
    padInitializeDefault(&pad);

    printf("\x1b[1;32m--- Minecraft Modern Launcher (1.20.1) ---\x1b[0m\n");
    printf("Support: Forge + Create + Mekanism\n\n");

    // 2. Préparation des arguments de la JVM
    std::string classpath = buildClasspath();
    
    JavaVM *jvm;
    JNIEnv *env;
    JavaVMInitArgs vm_args;
    JavaVMOption options[4];

    // On passe le classpath généré dynamiquement
    options[0].optionString = (char*)classpath.c_str();
    // Allocation de 2 Go de RAM (le maximum stable sur Switch)
    options[1].optionString = (char*)"-Xmx2G";
    // Optimisation du Garbage Collector pour éviter les saccades avec Create
    options[2].optionString = (char*)"-XX:+UseG1GC";
    // Désactivation de la vérification des classes pour gagner du temps au boot
    options[3].optionString = (char*)"-Xverify:none";

    vm_args.version = JNI_VERSION_17; // Java 17 pour Minecraft 1.20.1
    vm_args.nOptions = 4;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = JNI_FALSE;

    printf("Lancement de la JVM Java 17... (Veuillez patienter)\n");

    // 3. Création de la machine virtuelle
    jint res = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);

    if (res == JNI_OK) {
        printf("\n\x1b[1;34m[JVM INTERFACE]\x1b[0m Java est actif.\n");
        printf("Chargement de Forge 1.20.1 en cours...\n");
        
        // C'est ici que Forge prend le relais pour charger Create et Mekanism.
        // Pour un test simple, on ne fait rien de plus pour l'instant.
        
    } else {
        printf("\x1b[1;31mErreur Critique JVM : %d\x1b[0m\n", res);
        printf("Verifiez que libjvm.so est bien present.\n");
    }

    printf("\nAppuyez sur (+) et (-) simultanement pour quitter.\n");

    // Boucle principale
    while (appletMainLoop()) {
        padUpdate(&pad);
        u64 kDown = padGetButtonsDown(&pad);

        // Quitter proprement
        if ((kDown & HidNpadButton_Plus) && (kDown & HidNpadButton_Minus)) break;

        consoleUpdate(NULL);
    }

    // Nettoyage
    if (res == JNI_OK) jvm->DestroyJavaVM();
    romfsExit();
    consoleExit(NULL);
    return 0;
}
