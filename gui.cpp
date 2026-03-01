#include <switch.h>
#include <stdio.h>

// Couleurs (Format RGBA simple pour la console)
#define CLR_BG     "\x1b[48;5;235m" // Gris très foncé (Fond)
#define CLR_GREEN  "\x1b[48;5;28m"  // Vert Minecraft (Bouton)
#define CLR_RESET  "\x1b[0m"

void drawInterface(int selectedOption) {
    // Effacer l'écran et mettre le fond
    printf("\x1b[1;1H"); // Retour en haut à gauche
    
    printf("\n\n    " CLR_GREEN "  JAVA SWITCH LAUNCHER  " CLR_RESET "\n");
    printf("    ==========================\n\n");

    // Bouton JOUER
    if (selectedOption == 0) {
        printf("    " CLR_GREEN " > [   JOUER   ] < " CLR_RESET "\n\n");
    } else {
        printf("    [   JOUER   ]\n\n");
    }

    // Bouton PARAMÈTRES
    if (selectedOption == 1) {
        printf("    " CLR_GREEN " > [ PARAMETRES ] < " CLR_RESET "\n\n");
    } else {
        printf("    [ PARAMETRES ]\n\n");
    }

    printf("\n\n    (A) Sélectionner  |  (+) Quitter");
}

int main(int argc, char **argv) {
    consoleInit(NULL);
    padConfigureDefault(1, &padInitializationParametersDefault);
    PadState pad;
    padInitializeDefault(&pad);

    int selected = 0;

    while (appletMainLoop()) {
        padUpdate(&pad);
        u64 kDown = padKeysDown(&pad);

        // Navigation simple
        if (kDown & HidNpadButton_AnyDown || kDown & HidNpadButton_AnyUp) {
            selected = (selected == 0) ? 1 : 0;
        }

        if (kDown & HidNpadButton_A) {
            printf("\x1b[15;4H Lancement de Minecraft en cours...");
            // C'est ici qu'on appellera ton code de lancement plus tard
        }

        if (kDown & HidNpadButton_Plus) break;

        drawInterface(selected);
        consoleUpdate(NULL);
    }

    consoleExit(NULL);
    return 0;
}
