#ifndef CLASSE_H
#define CLASSE_H

enum niveau { LICENCE, MASTER, DOCTORAT };

struct classe {
    int code;
    char nom[50];
    enum niveau niveau_actuel;
};

int ajouter_classe();
void afficher_classes();
int supprimer_classe(int code);
int modifier_classe(int code);
void rechercher_classe();
void MenuGestionClasses();
void afficher_etudiants_par_classe(int code );

#endif
