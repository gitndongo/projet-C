#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"classe.h"
#include"matiere.h"
#include"notes.h"
#include"etudiants.h"


int main() {
    int choix;
    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Gestion des matières\n");
        printf("2. Gestion des étudiants\n");
        printf("3. Gestion des classes\n");
        printf("4. Gestion des notes\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: menugestionmatiere(); break;
            case 2: menuEtudiants(); break;
            case 3: MenuGestionClasses(); break;
            case 4: menuNotes(); break;
            case 0: printf("Merci, au revoir !\n"); break;
            default: printf("Choix invalide.\n");
        }
    } while (choix != 0);

    return 0;
}
