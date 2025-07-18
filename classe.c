#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "classe.h"

#define FICHIER_CSV "classes.csv"

int ajouter_classe() {
    struct classe nouvelle_classe;
    FILE *f = fopen(FICHIER_CSV, "a");
    if (!f) {
        printf("Erreur d'ouverture du fichier %s\n", FICHIER_CSV);
        return -1;
    }

    printf("Entrez le nom de la classe: ");
    scanf("%s", nouvelle_classe.nom);
    printf("Entrez le code de la classe: ");
    scanf("%d", &nouvelle_classe.code);
    printf("Entrez le niveau actuel (0 pour licence, 1 pour master, 2 pour doctorat): ");
    int niveau;
    scanf("%d", &niveau);

    if (niveau < 0 || niveau > 2) {
        printf("❌ Niveau invalide. Veuillez entrer 0, 1 ou 2.\n");
        fclose(f);
        return -1;
    }

    nouvelle_classe.niveau_actuel = (enum niveau)niveau;

    // Sauvegarde CSV
    fprintf(f, "%d,%s,%d\n", nouvelle_classe.code, nouvelle_classe.nom, nouvelle_classe.niveau_actuel);
    fclose(f);
    printf("✅ Classe ajoutée avec succès.\n");

    return 0;
}

void afficher_classes() {
    struct classe c;
    char ligne[100];
    FILE *f = fopen(FICHIER_CSV, "r");
    if (!f) {
        printf("Aucune classe enregistrée.\n");
        return;
    }

    printf("\nListe des classes enregistrées :\n");
    while (fgets(ligne, sizeof(ligne), f)) {
        sscanf(ligne, "%d,%49[^,],%d", &c.code, c.nom, (int *)&c.niveau_actuel);
        printf("Code : %d | Nom : %s | Niveau : %d\n", c.code, c.nom, c.niveau_actuel);
    }
    fclose(f);
}

int supprimer_classe(int code) {
    struct classe c;
    char ligne[100];
    FILE *f = fopen(FICHIER_CSV, "r");
    if (!f) {
        printf("Aucune classe enregistrée.\n");
        return -1;
    }

    FILE *temp = fopen("temp.csv", "w");
    if (!temp) {
        fclose(f);
        printf("Erreur de création du fichier temporaire.\n");
        return -1;
    }

    int trouve = 0;
    while (fgets(ligne, sizeof(ligne), f)) {
        sscanf(ligne, "%d,%49[^,],%d", &c.code, c.nom, (int *)&c.niveau_actuel);
        if (c.code != code) {
            fprintf(temp, "%d,%s,%d\n", c.code, c.nom, c.niveau_actuel);
        } else {
            trouve = 1;
        }
    }

    fclose(f);
    fclose(temp);

    if (trouve) {
        remove(FICHIER_CSV);
        rename("temp.csv", FICHIER_CSV);
        printf("✅ Classe avec code %d supprimée.\n", code);
    } else {
        remove("temp.csv");
        printf("❌ Classe avec code %d non trouvée.\n", code);
    }

    return trouve ? 0 : -1;
}

int modifier_classe(int code) {
    struct classe c;
    char ligne[100];
    FILE *f = fopen(FICHIER_CSV, "r");
    if (!f) {
        printf("Aucune classe enregistrée.\n");
        return -1;
    }

    FILE *temp = fopen("temp.csv", "w");
    if (!temp) {
        fclose(f);
        printf("Erreur de création du fichier temporaire.\n");
        return -1;
    }

    int trouve = 0;
    while (fgets(ligne, sizeof(ligne), f)) {
        sscanf(ligne, "%d,%49[^,],%d", &c.code, c.nom, (int *)&c.niveau_actuel);
        if (c.code == code) {
            trouve = 1;
            printf("Modifier le nom de la classe (actuel: %s): ", c.nom);
            scanf("%s", c.nom);
            printf("Modifier le niveau actuel (0 pour licence, 1 pour master, 2 pour doctorat): ");
            int niveau;
            scanf("%d", &niveau);
            if (niveau < 0 || niveau > 2) {
                printf("❌ Niveau invalide. Veuillez entrer 0, 1 ou 2.\n");
                fclose(f);
                fclose(temp);
                return -1;
            }
            c.niveau_actuel = (enum niveau)niveau;
        }
        fprintf(temp, "%d,%s,%d\n", c.code, c.nom, c.niveau_actuel);
    }

    fclose(f);
    fclose(temp);

    if (trouve) {
        remove(FICHIER_CSV);
        rename("temp.csv", FICHIER_CSV);
        printf("✅ Classe avec code %d modifiée.\n", code);
    } else {
        remove("temp.csv");
        printf("❌ Classe avec code %d non trouvée.\n", code);
    }

    return trouve ? 0 : -1;
}

void rechercher_classe() {
    int codeRecherche;
    struct classe c;
    char ligne[100];
    int trouve = 0;

    printf("Entrez le code de la classe à rechercher : ");
    scanf("%d", &codeRecherche);

    FILE *f = fopen(FICHIER_CSV, "r");
    if (!f) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", FICHIER_CSV);
        return;
    }

    while (fgets(ligne, sizeof(ligne), f)) {
        sscanf(ligne, "%d,%49[^,],%d", &c.code, c.nom, (int *)&c.niveau_actuel);
        if (c.code == codeRecherche) {
            printf("✅ Classe trouvée !\n");
            printf("Code : %d\n", c.code);
            printf("Nom : %s\n", c.nom);
            printf("Niveau : %d\n", c.niveau_actuel);
            trouve = 1;
            break;
        }
    }

    fclose(f);

    if (!trouve) {
        printf("❌ Classe non trouvée.\n");
    }
}

void afficher_etudiants_par_classe(int code) {
    FILE *f = fopen("etudiants.csv", "r");
    if (!f) {
        printf("❌ Erreur : impossible d'ouvrir le fichier etudiants.csv\n");
        return;
    }

    char ligne[200];
    int id, classe;
    char nom[50], prenom[50];
    int trouve = 0;

    printf("\n👥 Étudiants de la classe %d :\n", code);
    printf("--------------------------------------------------\n");

    while (fgets(ligne, sizeof(ligne), f)) {
        sscanf(ligne, "%d,%49[^,],%49[^,],%d", &id, nom, prenom, &classe);
        if (classe == code) {
            printf("ID : %d | Nom : %s %s\n", id, prenom, nom);
            trouve = 1;
        }
    }

    fclose(f);

    if (!trouve) {
        printf("Aucun étudiant trouvé dans cette classe.\n");
    }
}

void MenuGestionClasses() {
    int choix, code;

    do {
        printf("\n");
        printf("╔══════════════════════════════════════════════╗\n");
        printf("║         🏫  MENU GESTION DES CLASSES         ║\n");
        printf("╠══════════════════════════════════════════════╣\n");
        printf("║ 1. ➕ Ajouter une classe                     ║\n");
        printf("║ 2. 📄 Afficher toutes les classes            ║\n");
        printf("║ 3. ✏️  Modifier une classe                    ║\n");
        printf("║ 4. ❌ Supprimer une classe                   ║\n");
        printf("║ 5. 🔍 Rechercher une classe                  ║\n");
        printf("║ 6. 👨 Voir les étudiants d'une classe        ║\n");
        printf("║ 0. 🔙 Retour au menu principal               ║\n");
        printf("╚══════════════════════════════════════════════╝\n");
        printf("Votre choix => ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouter_classe();
                break;
            case 2:
                afficher_classes();
                break;
            case 3:
                printf("🔧 Entrez le code de la classe à modifier : ");
                scanf("%d", &code);
                modifier_classe(code);
                break;
            case 4:
                printf("🗑️  Entrez le code de la classe à supprimer : ");
                scanf("%d", &code);
                supprimer_classe(code);
                break;
            case 5:
                rechercher_classe();
                break;
            case 6:
                printf("📘 Entrez le code de la classe : ");
                scanf("%d", &code);
                afficher_etudiants_par_classe(code);
                break;
            case 0:
                printf("🔙 Retour au menu principal...\n");
                break;
            default:
                printf("⚠️  Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 0);
}
