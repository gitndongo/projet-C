#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "classe_matiere.h"

int classe_existe(int code_classe);
int matiere_existe(int ref_matiere);

void ajouter_classe_matiere() {
    int code_classe, ref_matiere;
    printf("Code de la classe : ");
    scanf("%d", &code_classe);
    printf("Référence de la matière : ");
    scanf("%d", &ref_matiere);

    FILE *f = fopen("classe_matiere.csv", "a");
    if (!f) {
        printf("Erreur d'ouverture de classe_matiere.csv\n");
        return;
    }

    fprintf(f, "%d,%d\n", code_classe, ref_matiere);
    fclose(f);

    printf("✅ Matière associée à la classe avec succès.\n");
}

void afficher_matieres_classe(int code_classe) {
    FILE *f_rel = fopen("classe_matiere.csv", "r");
    FILE *f_mat = fopen("matiere.csv", "r");
    if (!f_rel || !f_mat) {
        printf("Erreur d'ouverture de fichiers.\n");
        return;
    }

    int ref_matiere, code;
    char ligne[200];
    int matieres[100];
    int count = 0;

    while (fgets(ligne, sizeof(ligne), f_rel)) {
        sscanf(ligne, "%d,%d", &code, &ref_matiere);
        if (code == code_classe) {
            matieres[count++] = ref_matiere;
        }
    }
    fclose(f_rel);

    if (count == 0) {
        printf(" Aucune matière trouvée pour la classe %d.\n", code_classe);
        fclose(f_mat);
        return;
    }

    printf(" Matières de la classe %d :\n", code_classe);
    while (fgets(ligne, sizeof(ligne), f_mat)) {
        int ref;
        char libelle[50];
        int coef;
        sscanf(ligne, "%d,%49[^,],%d", &ref, libelle, &coef);
        for (int i = 0; i < count; i++) {
            if (ref == matieres[i]) {
                printf("- %s (ref: %d, coef: %d)\n", libelle, ref, coef);
            }
        }
    }

    fclose(f_mat);
}

void supprimer_matiere_de_classe() {
    int code_classe, ref_matiere;
    printf("Code de la classe : ");
    scanf("%d", &code_classe);
    printf("Référence de la matière à supprimer : ");
    scanf("%d", &ref_matiere);

    FILE *f_old = fopen("classe_matiere.csv", "r");
    FILE *f_new = fopen("temp.csv", "w");
    if (!f_old || !f_new) {
        printf("Erreur d'ouverture de fichier.\n");
        return;
    }

    int c, r;
    char ligne[200];
    int trouve = 0;

    while (fgets(ligne, sizeof(ligne), f_old)) {
        sscanf(ligne, "%d,%d", &c, &r);
        if (c == code_classe && r == ref_matiere) {
            trouve = 1; // on ignore cette ligne
            continue;
        }
        fprintf(f_new, "%d,%d\n", c, r);
    }

    fclose(f_old);
    fclose(f_new);
    remove("classe_matiere.csv");
    rename("temp.csv", "classe_matiere.csv");

    if (trouve)
        printf("Matière supprimee de la classe.\n");
    else
        printf(" Aucune association trouvee pour supprimer.\n");
}

void modifier_matiere_de_classe() {
    int code_classe, ancienne_ref, nouvelle_ref;
    printf("Code de la classe : ");
    scanf("%d", &code_classe);

    if (!classe_existe(code_classe)) {
        printf("❌ La classe %d n'existe pas dans classe_matiere.csv.\n", code_classe);
        return;
    }

    printf("Référence actuelle de la matière : ");
    scanf("%d", &ancienne_ref);
    if (!matiere_existe(ancienne_ref)) {
        printf("❌ La matière %d n'existe pas dans matiere.csv.\n", ancienne_ref);
        return;
    }

    printf("Nouvelle référence de la matière : ");
    scanf("%d", &nouvelle_ref);
    if (!matiere_existe(nouvelle_ref)) {
        printf("❌ La nouvelle matière %d n'existe pas dans matiere.csv.\n", nouvelle_ref);
        return;
    }

    FILE *f_old = fopen("classe_matiere.csv", "r");
    FILE *f_new = fopen("temp.csv", "w");
    if (!f_old || !f_new) {
        printf("Erreur d'ouverture de fichier.\n");
        return;
    }

    int c, r;
    char ligne[200];
    int modifie = 0;

    while (fgets(ligne, sizeof(ligne), f_old)) {
        sscanf(ligne, "%d,%d", &c, &r);
        if (c == code_classe && r == ancienne_ref) {
            fprintf(f_new, "%d,%d\n", c, nouvelle_ref);
            modifie = 1;
        } else {
            fprintf(f_new, "%d,%d\n", c, r);
        }
    }

    fclose(f_old);
    fclose(f_new);
    remove("classe_matiere.csv");
    rename("temp.csv", "classe_matiere.csv");

    if (modifie)
        printf("✅ Matière modifiée avec succès dans la classe.\n");
    else
        printf("❌ Aucune correspondance trouvée à modifier.\n");
}

// 🔎 Vérifie si une classe existe dans classe_matiere.csv
int classe_existe(int code_classe) {
    FILE *f = fopen("classe_matiere.csv", "r");
    if (!f) return 0;

    int c, r;
    char ligne[200];
    while (fgets(ligne, sizeof(ligne), f)) {
        sscanf(ligne, "%d,%d", &c, &r);
        if (c == code_classe) {
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}

// 🔎 Vérifie si une matière existe dans matiere.csv
int matiere_existe(int ref_matiere) {
    FILE *f = fopen("matiere.csv", "r");
    if (!f) return 0;

    int ref, coef;
    char libelle[50], ligne[200];
    while (fgets(ligne, sizeof(ligne), f)) {
        sscanf(ligne, "%d,%49[^,],%d", &ref, libelle, &coef);
        if (ref == ref_matiere) {
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}
