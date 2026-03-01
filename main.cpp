#include <switch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <jni.h> 

// --- CONFIGURATION DES CHEMINS ---
const char* BASE_PATH = "sdmc:/switch/javaswitch";
const char* JRE_PATH  = "sdmc:/switch/javaswitch/runtime/bin/java";
const char* MODS_PATH = "sdmc:/switch/javaswitch/minecraft/mods";
const char* ZIP_URL   = "https://github.com/PojavLauncherTeam/PojavLauncher-Switch/releases/download/v1.0/jre8-arm64.zip";

// --- VARIABLES GLOBALES ---
char username[32] = "Pamplemouche"; 

// --- FONCTIONS RÉSEAU (CURL) ---
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fwrite(ptr, size, nmemb, stream);
}

bool downloadFile(const char* url, const char* outPath) {
    CURL *curl = curl_easy_init();
    if (!curl) return false;

    FILE *fp = fopen(outPath, "wb");
    if (!fp) return false;

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    fclose(fp);
    return (res == CURLE_OK);
}

// --- LOGIQUE DE LANCEMENT JNI (MINECRAFT + MODS) ---
void launchMinecraft() {
    printf("\x1b[15;5H Preparation de la JVM...\n");

    JavaVM *jvm;
    JNIEnv *env;
    JavaVMInitArgs vm_args;
    JavaVMOption options[4];

    char classpath[512];
    // On charge le client et forge s'il est present
    sprintf(classpath, "-Djava.class.path=%s/minecraft/client.jar:%s/minecraft/forge.jar", BASE_PATH, BASE_PATH);
    
    options[0].optionString = classpath;
    options[1].optionString = (char*)"-Xmx2G"; 
    options[2].optionString = (char*)"-Dminecraft.app.dir=sdmc:/switch/javaswitch/minecraft";
    
    vm_args.version = JNI_VERSION_1_8;
    vm_args.nOptions = 3;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = JNI_FALSE;

    if (JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args) != JNI_OK) {
        printf("\x1b[17;5H Erreur: Impossible de charger la JVM (libjvm.so)\n");
        return;
    }

    jclass mainClass = env->FindClass("net/minecraft/client/main/Main"); 
    if (mainClass) {
        jmethodID mainMethod = env->GetStaticMethodID(mainClass, "main", "([Ljava/lang/String;)V");
        
        jobjectArray args = env->NewObjectArray(2, env->FindClass("java/lang/String"), env->NewStringUTF(""));
        env->SetObjectArrayElement(args, 0, env->NewStringUTF("--username"));
        env->SetObjectArrayElement(args, 1, env->NewStringUTF(username));

        env->CallStaticVoidMethod(mainClass, mainMethod, args);
    } else {
        printf("\x1b[17;5H Erreur: Minecraft client.jar introuvable.\n");
    }
}

// --- INTERFACE GRAPHIQUE ---
void drawUI(int selected) {
    printf("\x1b[1;1H\x1b[48;5;22m\x1b[38;5;255m"); 
    printf(" ############################################# \n");
    printf(" #       MINECRAFT JAVA SWITCH EDITION       # \n");
    printf(" ############################################# \n\x1b[0m\n");

    printf("\x1b[8;10H%s [ JOUER (Offline) ] %s", (selected == 0 ? "\x1b[42m >" : "  "), "\x1b[0m");
    printf("\x1b[10;10H%s [ MODS & SETTINGS ] %s", (selected == 1 ? "\x1b[42m >" : "  "), "\x1b[0m");
    
    printf("\x1b[13;10H Joueur actuel : %s", username);
    printf("\x1b[20;5H (A) Lancer  |  (Y) Pseudo  |  (+) Quitter ");
}

// --- BOUCLE PRINCIPALE ---
int main(int argc, char **argv) {
    consoleInit(NULL);
    socketInitializeDefault();
    curl_global_init(CURL_GLOBAL_DEFAULT);

    mkdir(BASE_PATH, 0777);
    mkdir(MODS_PATH, 0777);

    PadState pad;
    padInitializeDefault(&pad);
    int selected = 0;

    while (appletMainLoop()) {
        padUpdate(&pad);
        u64 kDown = padKeysDown(&pad);

        if (kDown & HidNpadButton_AnyUp || kDown & HidNpadButton_AnyDown) selected = (selected == 0) ? 1 : 0;

        if (kDown & HidNpadButton_A) {
            if (selected == 0) {
                if (access(JRE_PATH, F_OK) == -1) {
                    printf("\x1b[17;5H Telechargement de la JRE...\n");
                    downloadFile(ZIP_URL, "sdmc:/switch/javaswitch/java.zip");
                    printf("\x1b[18;5H Termine ! Veuillez extraire java.zip sur PC.\n");
                } else {
                    launchMinecraft();
                }
            }
        }

        if (kDown & HidNpadButton_Plus) break;

        drawUI(selected);
        consoleUpdate(NULL);
    }

    curl_global_cleanup();
    socketExit();
    consoleExit(NULL);
    return 0;
}
