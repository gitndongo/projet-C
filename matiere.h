#ifndef MATIERE_H
#define MATIERE_H

typedef struct {
    int id_matiere;
    char nom_matiere[20];
    int coef;
} Matiere;

void ajoutermatiere();
// void modifiermatiere();
// void supprimermatiere();
// void recherchermatiere();
// void affichermatiere();
void menugestionmatiere();

#endif
