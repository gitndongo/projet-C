#include <stdio.h>
#include <stdlib.h>
#include "notes.h"
#include<stdbool.h>
#include <string.h>
#include"etudiants.h"



bool etudiantExiste(int id) {
    FILE *f = fopen("etudiants.csv", "r");
    if (!f) {
        printf("Erreur : impossible d'ouvrir etudiants.csv\n");
        return false;
    }

    int id_temp;
    char ligne[256];

    while (fgets(ligne, sizeof(ligne), f)) {
        sscanf(ligne, "%d", &id_temp);
        if (id_temp == id) {
            fclose(f);
            return true;
        }
    }

    fclose(f);
    return false;
}


bool matiereExiste(int id) {
    FILE *f = fopen("matiere.csv", "r");
    if (!f) {
        printf("Erreur : impossible d'ouvrir matieres.csv\n");
        return false;
    }

    int id_temp;
    char ligne[256];

    while (fgets(ligne, sizeof(ligne), f)) {
        sscanf(ligne, "%d", &id_temp);
        if (id_temp == id) {
            fclose(f);
            return true;
        }
    }

    fclose(f);
    return false;
}



void ajouterNote() {
    Note n;

    printf("ID etudiant : ");
    scanf("%d", &n.etudiant_id);

    // Vérification de l'existence de l'étudiant
    if (!etudiantExiste(n.etudiant_id)) {
        printf("Erreur : l'étudiant avec l'ID %d n'existe pas.\n", n.etudiant_id);
        return;
    }

    printf("ID matiere : ");
    scanf("%d", &n.matiere_id);

    if (!matiereExiste(n.matiere_id)) {
        printf("Erreur : la matière avec l'ID %d n'existe pas.\n", n.matiere_id);
        return;
    }

    printf("Note CC : ");
    scanf("%f", &n.note_cc);
    printf("Note DS : ");
    scanf("%f", &n.note_ds);

    FILE *f = fopen("notes.csv", "a");
    if (!f) {
        printf("Erreur : impossible d'ouvrir notes.csv\n");
        return;
    }

    fprintf(f, "%d,%d,%.2f,%.2f\n", n.etudiant_id, n.matiere_id, n.note_cc, n.note_ds);
    fclose(f);

    printf("Note ajoutée avec succès.\n");
}


void modifierNote() 
{
    FILE *f = fopen("notes.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    if (!f || !temp) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    int etu_id, mat_id;
    printf("ID etudiant : ");
    scanf("%d", &etu_id);
     if (!etudiantExiste(etu_id)) {
        printf("Erreur : l'étudiant avec l'ID %d n'existe pas.\n", etu_id);
        return; }
    printf("ID matiere : ");
    scanf("%d", &mat_id);
     if (!matiereExiste(mat_id)) {
        printf("Erreur : la matière avec l'ID %d n'existe pas.\n", mat_id);
        return; }

    Note n;
    int trouve = 0;

    while (fscanf(f, "%d,%d,%f,%f\n", &n.etudiant_id, &n.matiere_id, &n.note_cc, &n.note_ds) != EOF) {
        if (n.etudiant_id == etu_id && n.matiere_id == mat_id) {
            printf("Nouvelle note CC : ");
            scanf("%f", &n.note_cc);
            printf("Nouvelle note DS : ");
            scanf("%f", &n.note_ds);
            trouve = 1;
        }
        fprintf(temp, "%d,%d,%.2f,%.2f\n", n.etudiant_id, n.matiere_id, n.note_cc, n.note_ds);
    }

    fclose(f);
    fclose(temp);
    remove("notes.csv");
    rename("temp.csv", "notes.csv");

    if (trouve)
        printf("Note modifiee avec succes.\n");
    else
        printf("Note non trouvee.\n");
}

void supprimerNote()
{
    FILE *f = fopen("notes.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    if (!f || !temp) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    int etu_id, mat_id;
    printf("ID etudiant : ");
    scanf("%d", &etu_id);
    printf("ID matiere : ");
    scanf("%d", &mat_id);

    Note n;
    int trouve = 0;

    while (fscanf(f, "%d,%d,%f,%f\n", &n.etudiant_id, &n.matiere_id, &n.note_cc, &n.note_ds) != EOF) {
        if (n.etudiant_id == etu_id && n.matiere_id == mat_id) {
            trouve = 1;
            continue; // Ne pas recopier = supprimer
        }
        fprintf(temp, "%d,%d,%.2f,%.2f\n", n.etudiant_id, n.matiere_id, n.note_cc, n.note_ds);
    }

    fclose(f);
    fclose(temp);
    remove("notes.csv");
    rename("temp.csv", "notes.csv");

    if (trouve)
        printf("Note supprimee avec succes.\n");
    else
        printf("Note non trouvee.\n");
}

void afficherNotesEtudiant()    // pour afficher note d'un etudiant 
 {
    int etu_id;
    printf("ID de l'etudiant : ");
    scanf("%d", &etu_id);

    FILE *f = fopen("notes.csv", "r");
    if (!f) {
        printf("Erreur : fichier notes.csv introuvable.\n");
        return;
    }

    Note n;
    int trouve = 0;

    printf("Notes de l'etudiant %d :\n", etu_id);

    while (fscanf(f, "%d,%d,%f,%f\n", &n.etudiant_id, &n.matiere_id, &n.note_cc, &n.note_ds) != EOF) {
        if (n.etudiant_id == etu_id) {
            printf("Matiere ID: %d | CC: %.2f | DS: %.2f\n", n.matiere_id, n.note_cc, n.note_ds);
            trouve = 1;
        }
    }

    if (!trouve)
        printf("Aucune note trouvee pour cet etudiant.\n");

    fclose(f);
}


bool classeExiste(int code) {
    FILE *f = fopen("classes.csv", "r");
    if (!f) {
        printf("Erreur : impossible d'ouvrir classes.csv\n");
        return false;
    }

    int code_lu;
    char nom[50];
    char ligne[100];

    while (fgets(ligne, sizeof(ligne), f)) {
        if (sscanf(ligne, "%d,%49[^\n]", &code_lu, nom) == 2) {
            if (code_lu == code) {
                fclose(f);
                return true;
            }
        }
    }

    fclose(f);
    return false;
}

void afficherNotesClasse() {
    int classe_id;
    printf("ID de la classe : ");
    scanf("%d", &classe_id);

    if (!classeExiste(classe_id)) {
        printf("❌ La classe %d n'existe pas.\n", classe_id);
        return;
    }

    FILE *f_etud = fopen("etudiants.csv", "r");
    FILE *f_notes = fopen("notes.csv", "r");
    if (!f_etud || !f_notes) {
        printf("Erreur : impossible d'ouvrir les fichiers.\n");
        if (f_etud) fclose(f_etud);
        if (f_notes) fclose(f_notes);
        return;
    }

    Etudiant e;
    Note n;
    int trouve_etudiant = 0;

    printf("\n📚 Notes des étudiants de la classe %d :\n", classe_id);

    while (fscanf(f_etud, "%d,%49[^,],%49[^,],%d\n",
                  &e.id, e.nom, e.prenom, &e.codeClasse) != EOF) {
        if (e.codeClasse == classe_id) {
            trouve_etudiant = 1;
            int note_trouvee = 0;

            rewind(f_notes);  // recommencer la lecture des notes
            while (fscanf(f_notes, "%d,%d,%f,%f\n",
                          &n.etudiant_id, &n.matiere_id, &n.note_cc, &n.note_ds) != EOF) {
                if (n.etudiant_id == e.id) {
                    printf("Etudiant: %s %s (ID: %d) → Matière ID: %d | CC: %.2f | DS: %.2f\n",
                           e.nom, e.prenom, e.id, n.matiere_id, n.note_cc, n.note_ds);
                    note_trouvee = 1;
                }
            }

            if (!note_trouvee) {
                printf("Etudiant: %s %s (ID: %d) → Aucune note trouvée.\n",
                       e.nom, e.prenom, e.id);
            }
        }
    }

    if (!trouve_etudiant) {
        printf("📌 Aucun étudiant trouvé dans cette classe.\n");
    }

    fclose(f_etud);
    fclose(f_notes);
}


void menuNotes() {
    int choix;

    do {
        printf("\n\n");
        printf("╔══════════════════════════════════════════════════════════════════════╗\n");
        printf("║                 📊 GESTION DES NOTES                                 ║\n");
        printf("╠══════════════════════════════════════════════════════════════════════╣\n");
        printf("║ 1. ➕  Ajouter une note                                              ║\n");
        printf("║ 2. 🛠️  Modifier une note                                             ║\n");
        printf("║ 3. ❌  Supprimer une note                                            ║\n");
        printf("║ 4. 👨  Afficher notes d'un étudiant                                  ║\n");
        printf("║ 5. 🏫  Afficher notes d'une classe                                   ║\n");
        printf("║ 0. 🚪  Retour                                                        ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════╝\n");

        printf("🎯 Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: ajouterNote(); break;
            case 2: modifierNote(); break;
            case 3: supprimerNote(); break;
            case 4: afficherNotesEtudiant(); break;
            case 5: afficherNotesClasse(); break;
            case 0:
                printf("👋 Retour au menu principal.\n");
                break;
            default:
                printf("❌ Choix invalide. Veuillez réessayer.\n");
        }

    } while (choix != 6);
}
