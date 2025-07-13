#ifndef ETUDIANTS_H
#define ETUDIANTS_H

typedef struct {
    int id;
    char nom[100];
    char prenom[100];
    char codeClasse[50];
} Etudiant;

void ajouterEtudiant();
void afficherEtudiants();
void modifierEtudiant();
void supprimerEtudiant();
Etudiant chercherEtudiantParId(int id);
void menuEtudiants();

#endif
