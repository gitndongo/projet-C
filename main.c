#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include"matiere.h"

int main ()
{
 
    printf("======MENU PRINCIPALE=====\n\n");
    int choix;
    printf("Taper ** 1 **  pour acceder a la MENU de le GESTION des MATIERES  et  ** 0 ** pour QUITTER \n");
    
    do 
    {
            printf("1-)\t=====GESTION DES MATIERES=====\n");
           printf("0-)\t======QUITTER=====\n");
           printf("**Entrer votre choix** : ");
           scanf("%d", &choix);
           switch (choix)
            {
                case 1 : menugestionmatiere();
                    break;
                case 0 : printf("=====Fermeture du programme=====\n");
                    break;
                default : printf("Ce choix est invalide.\n");
            }

        }while (choix != 0 );

}