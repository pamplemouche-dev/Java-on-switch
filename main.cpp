#include <switch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <unistd.h>

// --- CONFIGURATION ---
const char* JRE_URL = "https://github.com/PojavLauncherTeam/PojavLauncher-Switch/releases/download/v1.0/jre8-arm64.zip"; // Exemple d'URL
const char* JRE_PATH = "sdmc:/switch/javaswitch/runtime/bin/java";
const char* ZIP_DEST = "sdmc:/switch/javaswitch/java.zip";

// --- FONCTIONS RÉSEAU ---
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fwrite(ptr, size, nmemb, stream);
}

bool downloadJRE() {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    bool success = false;

    curl = curl_easy_init();
    if (curl) {
        // Créer le dossier s'il n'existe pas
        mkdir("sdmc:/switch/javaswitch", 0777);
        
        fp = fopen(ZIP_DEST, "wb");
        if (!fp) return false;

        printf("\x1b[15;5H Téléchargement en cours... Patientez.\n");
        
        curl_easy_setopt(curl, CURLOPT_URL, JRE_URL);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

        res = curl_easy_perform(curl);
        if(res == CURLE_OK) success = true;

        curl_easy_cleanup(curl);
        fclose(fp);
    }
    return success;
}

// --- INTERFACE ---
void drawUI(int selected) {
    printf("\x1b[1;1H"); // Reset curseur
    printf("\x1b[48;5;22m\x1b[38;5;255m"); // Fond Vert / Texte Blanc
    printf(" ############################################# \n");
    printf(" #          JAVA ON SWITCH LAUNCHER          # \n");
    printf(" ############################################# \n\x1b[0m\n");

    printf("\x1b[8;10H%s [  JOUER  ] %s", (selected == 0 ? "\x1b[42m >" : "  "), "\x1b[0m");
    printf("\x1b[10;10H%s [ SETTINGS ] %s", (selected == 1 ? "\x1b[42m >" : "  "), "\x1b[0m");
    
    printf("\x1b[20;5H (A) Sélectionner  |  (+) Quitter ");
}

// --- MAIN ---
int main(int argc, char **argv) {
    consoleInit(NULL);
    socketInitializeDefault();
    curl_global_init(CURL_GLOBAL_DEFAULT);

    PadState pad;
    padInitializeDefault(&pad);

    int selected = 0;
    bool running = true;

    while (appletMainLoop() && running) {
        padUpdate(&pad);
        u64 kDown = padKeysDown(&pad);

        if (kDown & HidNpadButton_AnyUp || kDown & HidNpadButton_AnyDown) {
            selected = (selected == 0) ? 1 : 0;
        }

        if (kDown & HidNpadButton_A) {
            if (selected == 0) {
                // Vérifier si Java existe
                if (access(JRE_PATH, F_OK) == -1) {
                    if (downloadJRE()) {
                        printf("\x1b[17;5H Téléchargé ! Décompressez le ZIP sur PC pour l'instant.\n");
                    } else {
                        printf("\x1b[17;5H Erreur de téléchargement. Vérifiez internet.\n");
                    }
                } else {
                    printf("\x1b[17;5H Lancement de Minecraft...\n");
                    // Code de lancement JNI à venir
                }
            }
        }

        if (kDown & HidNpadButton_Plus) running = false;

        drawUI(selected);
        consoleUpdate(NULL);
    }

    curl_global_cleanup();
    socketExit();
    consoleExit(NULL);
    return 0;
}
