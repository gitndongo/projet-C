#include <stdio.h>
#include "notes.h"

void menuPrincipal() {
    int choix;
    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Gestion des notes\n");
        printf("2. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                menuNotes();
                break;
            case 2:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 2);
}

int main() {
    menuPrincipal();
    return 0;
}
