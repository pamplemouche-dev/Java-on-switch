#include <switch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <jni.h>

// Fonction pour télécharger des fichiers (utile pour le runtime Java)
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void downloadFile(const char* url, const char* outfilename) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outfilename, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }
}

int main(int argc, char **argv) {
    // Initialisation console
    consoleInit(NULL);

    // Initialisation des contrôles (Nouveau standard libnx)
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);
    PadState pad;
    padInitializeDefault(&pad);

    printf("JavaSwitch Launcher v1.0.0\n");
    printf("Appuyez sur + pour quitter.\n\n");

    // Exemple de logique JNI (Initialisation de la JVM)
    JavaVM *jvm;       
    JNIEnv *env;       
    JavaVMInitArgs vm_args;
    JavaVMOption options[1];
    
    // Chemin vers tes classes Java sur la SD
    options[0].optionString = (char*)"-Djava.class.path=sdmc:/java/apps/";
    vm_args.version = JNI_VERSION_1_8;
    vm_args.nOptions = 1;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = JNI_FALSE;

    printf("Chargement de la machine virtuelle Java...\n");
    
    // Note : Pour que cela fonctionne sur console réelle, 
    // il faut que les fichiers libjvm.so soient présents.
    
    while(appletMainLoop()) {
        // Lecture des touches
        padUpdate(&pad);
        u64 kDown = padGetButtonsDown(&pad);

        if (kDown & HidNpadButton_Plus) break;

        // Ta logique ici
        
        consoleUpdate(NULL);
    }

    consoleExit(NULL);
    return 0;
}
