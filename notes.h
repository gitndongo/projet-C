#ifndef NOTES_H
#define NOTES_H
#include<stdbool.h>

typedef struct {
    int etudiant_id;
    int matiere_id;
    float note_cc;
    float note_ds;
} Note;

void ajouterNote();
void modifierNote();
void supprimerNote();
void afficherNotesEtudiant();
void afficherNotesClasse();
void menuNotes();
bool etudiantExiste(int id);
bool  matiereExiste(int id);

#endif
