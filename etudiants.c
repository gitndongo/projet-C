#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "etudiants.h"

// Ajouter un etudiant
void ajouterEtudiant() {
    Etudiant e;
    FILE *f = fopen("etudiants.csv", "a");

    printf("ID : "); scanf("%d", &e.id);
    printf("Nom : "); scanf("%s", e.nom);
    printf("Prénom : "); scanf("%s", e.prenom);
    printf("Code classe : "); scanf("%d", &e.codeClasse);

    fprintf(f, "%d,%s,%s,%d\n", e.id, e.nom, e.prenom, e.codeClasse);
    fclose(f);
    printf("✅ Etudiant ajoute avec succes !\n");
}

// Afficher tous les etudiants
void afficherEtudiants() {
    FILE *f = fopen("etudiants.csv", "r");
    Etudiant e;
    char ligne[200];

    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }

   
    printf("Liste des étudiants :\n");
    int trouver = 0;
    while (fscanf(f, "%d,%19[^,],%19[^,],%d\n", &e.id, e.nom, e.prenom, &e.codeClasse)== 4) {
        printf("ID: %d | %s %s | Classe: %d\n", e.id, e.nom, e.prenom, e.codeClasse);
        trouver = 1;    
        
    }

    fclose(f);
    if (trouver) {
        printf("Tous les étudiants affichés.\n");
       
    }
    else
        printf("❌ Aucun étudiant trouvé.\n");
}



// Modifier un etudiant
void modifierEtudiant() {
    int id;
    printf("ID de l'étudiant à modifier : ");
    scanf("%d", &id);

    FILE *f = fopen("etudiants.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    Etudiant e;
    int trouve = 0;

    while (fscanf(f, "%d,%[^,],%[^,],%d\n", &e.id, e.nom, e.prenom, &e.codeClasse) != EOF) {
        if (e.id == id) {
            printf("Nouveau nom : "); scanf("%s", e.nom);
            printf("Nouveau prénom : "); scanf("%s", e.prenom);
            printf("Nouveau code classe : "); scanf("%d", &e.codeClasse);
            trouve = 1;
        }
        fprintf(temp, "%d,%s,%s,%d\n", e.id, e.nom, e.prenom, e.codeClasse);
    }

    fclose(f);
    fclose(temp);
    remove("etudiants.csv");
    rename("temp.csv", "etudiants.csv");

    if (trouve)
        printf("✅ Etudiant modifié !\n");
    else
        printf("❌ Etudiant non trouvé.\n");
}

// Supprimer un etudiant
void supprimerEtudiant() {
    int id;
    printf("ID de l'etudiant à supprimer : ");
    scanf("%d", &id);

    FILE *f = fopen("etudiants.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    Etudiant e;
    int trouve = 0;

    char ligne[100];
    fgets(ligne, sizeof(ligne), f); 
    fprintf(temp, "%s", ligne);     

    while (fscanf(f, "%d,%[^,],%[^,],%d\n", &e.id, e.nom, e.prenom, &e.codeClasse) != EOF) {
        if (e.id != id)
            fprintf(temp, "%d,%s,%s,%d\n", e.id, e.nom, e.prenom, e.codeClasse);
        else
            trouve = 1;
    }

    fclose(f);
    fclose(temp);
    remove("etudiants.csv");
    rename("temp.csv", "etudiants.csv");

    if (trouve)
        printf("✅ Etudiant supprimé !\n");
    else
        printf("❌ Etudiant non trouvé.\n");
}




void menuEtudiants() {
    int choix;
    do {
        printf("\n");
        printf("╔════════════════════════════════════════════╗\n");
        printf("║         🎓 MENU GESTION ÉTUDIANTS          ║\n");
        printf("╠════════════════════════════════════════════╣\n");
        printf("║ 1. ➕ Ajouter un étudiant                  ║\n");
        printf("║ 2. 📋 Afficher les étudiants               ║\n");
        printf("║ 3. ✏️  Modifier un étudiant                 ║\n");
        printf("║ 4. ❌  Supprimer un étudiant                ║\n");
        printf("║ 0. 🔙 Retour                               ║\n");
        printf("╚════════════════════════════════════════════╝\n");
        printf("Votre choix => ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterEtudiant();
                break;
            case 2:
                afficherEtudiants();
                break;
            case 3:
                modifierEtudiant();
                break;
            case 4:
                supprimerEtudiant();
                break;
            case 0:
                printf("🔙 Retour au menu précédent...\n");
                break;
            default:
                printf("⚠️  Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 0);
}