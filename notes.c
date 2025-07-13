#include <stdio.h>
#include <stdlib.h>
#include "notes.h"

void ajouterNote() {
    FILE *f = fopen("notes.csv", "a");
    if (!f) {
        printf("Erreur : impossible d'ouvrir notes.csv\n");
        return;
    }

    Note n;
    printf("ID etudiant : ");
    scanf("%d", &n.etudiant_id);
    printf("ID matiere : ");
    scanf("%d", &n.matiere_id);
    printf("Note CC : ");
    scanf("%f", &n.note_cc);
    printf("Note DS : ");
    scanf("%f", &n.note_ds);

    fprintf(f, "%d,%d,%.2f,%.2f\n", n.etudiant_id, n.matiere_id, n.note_cc, n.note_ds);
    fclose(f);

    printf("Note ajoutee avec succes.\n");
}

void modifierNote() {
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

void supprimerNote() {
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

void afficherNotesEtudiant() {
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

void afficherNotesClasse() {
    int classe_id;
    printf("ID de la classe : ");
    scanf("%d", &classe_id);

    FILE *f_etud = fopen("etudiants.csv", "r");
    if (!f_etud) {
        printf("Erreur : fichier etudiants.csv introuvable.\n");
        return;
    }

    FILE *f_notes = fopen("notes.csv", "r");
    if (!f_notes) {
        printf("Erreur : fichier notes.csv introuvable.\n");
        fclose(f_etud);
        return;
    }

    typedef struct {
        int id;
        char nom[50];
        char prenom[50];
        char sexe[10];
        char date_naissance[20];
        int classe_id;
    } Etudiant;

    Etudiant e;
    int note_trouvee = 0;

    printf("Notes des etudiants de la classe %d :\n", classe_id);

    while (fscanf(f_etud, "%d,%49[^,],%49[^,],%9[^,],%19[^,],%d\n",
                  &e.id, e.nom, e.prenom, e.sexe, e.date_naissance, &e.classe_id) != EOF) {
        if (e.classe_id == classe_id) {
            rewind(f_notes);

            Note n;
            int etu_trouve = 0;

            while (fscanf(f_notes, "%d,%d,%f,%f\n",
                          &n.etudiant_id, &n.matiere_id, &n.note_cc, &n.note_ds) != EOF) {
                if (n.etudiant_id == e.id) {
                    printf("Etudiant: %s %s (ID: %d), Matiere ID: %d, CC: %.2f, DS: %.2f\n",
                           e.nom, e.prenom, e.id, n.matiere_id, n.note_cc, n.note_ds);
                    etu_trouve = 1;
                    note_trouvee = 1;
                }
            }

            if (!etu_trouve) {
                printf("Etudiant: %s %s (ID: %d) n'a pas encore de notes.\n", e.nom, e.prenom, e.id);
            }
        }
    }

    if (!note_trouvee) {
        printf("Aucune note trouvee pour cette classe.\n");
    }

    fclose(f_etud);
    fclose(f_notes);
}

void menuNotes() {
    int choix;
    do {
        printf("\n=== Gestion des notes ===\n");
        printf("1. Ajouter une note\n");
        printf("2. Modifier une note\n");
        printf("3. Supprimer une note\n");
        printf("4. Afficher notes d'un etudiant\n");
        printf("5. Afficher notes d'une classe\n");
        printf("6. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterNote();
                break;
            case 2:
                modifierNote();
                break;
            case 3:
                supprimerNote();
                break;
            case 4:
                afficherNotesEtudiant();
                break;
            case 5:
                afficherNotesClasse();
                break;
            case 6:
                printf("Retour au menu principal.\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 6);
}
