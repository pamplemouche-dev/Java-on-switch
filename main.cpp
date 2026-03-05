#include <switch.h>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <cstring> // Ajout crucial pour strstr

// Sécurité pour la version JNI si non définie par le header
#ifndef JNI_VERSION_17
#define JNI_VERSION_17 0x00110000
#endif

std::string buildClasspath() {
    std::string cp = "-Djava.class.path=";
    DIR* dir = opendir("romfs:/mods");
    struct dirent* ent;
    bool first = true;

    if (dir) {
        while ((ent = readdir(dir)) != NULL) {
            if (strstr(ent->d_name, ".jar")) {
                if (!first) cp += ":";
                cp += "romfs:/mods/";
                cp += ent->d_name;
                first = false;
            }
        }
        closedir(dir);
    }
    return cp;
}

int main(int argc, char* argv[]) {
    consoleInit(NULL);
    romfsInit();
    
    PadState pad;
    padInitializeDefault(&pad);

    printf("\x1b[1;32m--- Minecraft Switch Launcher ---\x1b[0m\n");

    std::string classpath = buildClasspath();
    
    JavaVM *jvm;
    JNIEnv *env;
    JavaVMInitArgs vm_args;
    JavaVMOption options[4];

    options[0].optionString = (char*)classpath.c_str();
    options[1].optionString = (char*)"-Xmx2G";
    options[2].optionString = (char*)"-XX:+UseG1GC";
    options[3].optionString = (char*)"-Xverify:none";

    vm_args.version = JNI_VERSION_17; 
    vm_args.nOptions = 4;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = JNI_FALSE;

    printf("Lancement de la JVM...\n");

    jint res = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);

    if (res == JNI_OK) {
        printf("Java est pret. Lancement de Forge...\n");
    } else {
        printf("\x1b[1;31mErreur JVM : %d\x1b[0m\n", res);
    }

    while (appletMainLoop()) {
        padUpdate(&pad);
        u64 kDown = padGetButtonsDown(&pad);
        if ((kDown & HidNpadButton_Plus) && (kDown & HidNpadButton_Minus)) break;
        consoleUpdate(NULL);
    }

    if (res == JNI_OK) jvm->DestroyJavaVM();
    romfsExit();
    consoleExit(NULL);
    return 0;
}
