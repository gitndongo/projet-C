#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "matiere.h"
#include "classe_matiere.h"

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

void ajoutermatiere()
{
    FILE *f = fopen("matiere.csv", "a");
    if (f == NULL )
       {
           printf("Desole erreure d'ouverture du ficher \n");
           return;
        }
 Matiere m ;
 printf("*******AJOUT D'UNE MATIERE*******\n");
 printf("saisissez l'ID_de_ la_matiere : ");
 scanf("%d", &m.id_matiere);
 getchar();
 printf("Saisissez le NOM_de_la_matiere : ");
 fgets(m.nom_matiere, sizeof(m.nom_matiere), stdin);
 m.nom_matiere[strcspn(m.nom_matiere, "\n")] = '\0';

 printf("saisissez le COEF_la_matiere : ");
 scanf("%d", &m.coef);
 fprintf(f, "%d,%s,%d\n", m.id_matiere, m.nom_matiere, m.coef); 
    fclose(f);

    printf("Matiere ajouter avec succes  !\n\n");
    
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
 void modifiermatiere()
  {
    // 1. Ouverture des fichiers
    FILE *f = fopen("matiere.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    if (f == NULL || temp == NULL) {
        printf("===== Erreur d'ouverture des fichiers =====\n\n");
        return;
    }

    printf("\n======== Liste des matieres existantes ========\n");
    char ligne[100];
    while (fgets(ligne, sizeof(ligne), f)) 
    {
        printf("%s", ligne);
    }
    rewind(f); 

    int id_rechercher;
    printf("\n*** Entrez l'ID de la matiere a modifier : ");
    scanf("%d", &id_rechercher);
    getchar(); 

    
    Matiere m;
    int trouver = 0;
    while (fscanf(f, "%d,%19[^,],%d\n", &m.id_matiere, m.nom_matiere, &m.coef) == 3) {
        if (m.id_matiere == id_rechercher) {
            trouver = 1;
            printf("\n** Modification de la matiere ID %d **\n", m.id_matiere);
            printf("Ancien nom : %s\n", m.nom_matiere);
            printf("Nouveau nom : ");
            fgets(m.nom_matiere, sizeof(m.nom_matiere), stdin);
            m.nom_matiere[strcspn(m.nom_matiere, "\n")] = '\0';
            
            printf("Ancien coefficient : %d\n", m.coef);
            printf("Nouveau coefficient : ");
            scanf("%d", &m.coef);
            getchar(); 
        }
        fprintf(temp, "%d,%s,%d\n", m.id_matiere, m.nom_matiere, m.coef);
    }

    fclose(f);
    fclose(temp);
    
    if (trouver) {
        remove("matiere.csv");
        rename("temp.csv", "matiere.csv");
        printf("\n**** Matiere modifiee avec succes ****\n");
    } else {
        remove("temp.csv"); 
        printf("\n*** Matiere non trouvee - Verifiez l'ID ***\n");
    }
}


void supprimermatiere()
{

    FILE *f =fopen( "matiere.csv", "r");
    FILE *temp= fopen ("temp.csv ", "w");

    if ( f== NULL || temp == NULL )
        {
            printf("Erreur d'ouverture des fichers \n");
            return ;

        }

    int id_rechercher ;
    int trouve = 0 ;
    Matiere m ;

    printf("\n********SUPPRESSION D'UNE MATIERE*********\n\n ");
    printf("**Entrer l'ID de la matiere a supprimer : ");
    scanf("%d", &id_rechercher);
    getchar();
    while (fscanf(f, "%d,%19[^,],%d\n", &m.id_matiere, m.nom_matiere, &m.coef) == 3)
    {
        if ( id_rechercher == m.id_matiere)
            {
                trouve=1;
                continue;
            }
        fprintf(temp, "%d,%s,%d\n", m.id_matiere, m.nom_matiere, m.coef);

    }

  fclose(f);
  fclose(temp);

  remove ("matiere.csv");
  rename ("temp.csv", "matiere.csv");

  if (trouve)
    {
        printf("\n*****Matiere supprimer avec succes*******\n\n");

    }
else
printf("\n****Matiere non retrouver , verifier l'ID saisie *******");



}


void recherchermatiere()
{
    FILE *f = fopen("matiere.csv", "r");
    if (f == NULL)
    {
        printf("Desole ! Une erreur s'est produite lors de l'ouverture du fichier.\n");
        return;
    }

    int id_rechercher;
    int trouver = 0;
    Matiere m;

    printf("\n******** RECHERCHE D'UNE MATIERE ***********\n\n");
    printf("** Entrez l'ID de la matiere a rechercher : ");
    scanf("%d", &id_rechercher);
    getchar();

    while (fscanf(f, "%d,%19[^,],%d\n", &m.id_matiere, m.nom_matiere, &m.coef) == 3)
    {
        if (id_rechercher == m.id_matiere)
        {
            trouver = 1;
            printf("\n Matiere trouvee :\n");
            printf("%3d | %-19s | %3d\n", m.id_matiere, m.nom_matiere, m.coef);
            break; 
        }
    }

    fclose(f);

    if (!trouver)
    {
        printf("\nDesole ! Matiere non trouvee. Verifiez l'ID fourni.\n");
    }
}


void affichermatiere()
{
    FILE *f = fopen("matiere.csv", "r");
    if (f == NULL)
    {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }

    Matiere m;
    int vide = 1;

    printf("\n======== LISTE DES MATIERES ========\n");
    printf(" ID | Nom de la matiere       | Coef\n");
    printf("----------------------------------------\n");

    while (fscanf(f, "%d,%19[^,],%d\n", &m.id_matiere, m.nom_matiere, &m.coef) == 3)
    {
        printf("%3d | %-22s | %4d\n", m.id_matiere, m.nom_matiere, m.coef);
        vide = 0;
    }

    fclose(f);

    if (vide)
    {
        printf("Aucune matiere enregistree.\n");
    }
}


void menugestionmatiere()
{
    int choix;

    
    while (1)
    {
        printf("\n");
        printf("╔══════════════════════════════════════════════════════════╗\n");
        printf("║       📚MENU DE LA GESTION DES MATIER                    ║\n");
        printf("╠══════════════════════════════════════════════════════════╣\n");
        printf("║ 1. ➕  Ajouter une matière                               ║\n");
        printf("║ 2. 🛠️  Modifier une matière                              ║\n");
        printf("║ 3. ❌  Supprimer une matière                             ║\n");
        printf("║ 4. 🔍  Rechercher une matière                            ║\n");
        printf("║ 5. 📋  Afficher toutes les matières                      ║\n");
        printf("║ 6. 🔗  Associer une matière à une classe                 ║\n");
        printf("║ 7. 🧾  Afficher les matières d'une classe                ║\n");
        printf("║ 8. 📝  Modifier une matière d'une classe                 ║\n");
        printf("║ 9. ❌  Supprimer une matière d'une classe                ║\n");
        printf("║ 0. 🚪  quitter                                           ║\n");
        printf("╚══════════════════════════════════════════════════════════╝\n");

        printf("🎯 Entrer votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
            case 1: ajoutermatiere(); break;
            case 2: modifiermatiere(); break;
            case 3: supprimermatiere(); break;
            case 4: recherchermatiere(); break;
            case 5: affichermatiere(); break;
            case 6: ajouter_classe_matiere(); break;
            case 7:
                {
                    int code;
                    printf("🔢 Code de la classe : ");
                    scanf("%d", &code);
                    afficher_matieres_classe(code);
                }
                break;
            case 8: modifier_matiere_de_classe(); break;
            case 9: supprimer_matiere_de_classe(); break;
            case 0:
                printf("👋 Fermeture de la gestion des matières...\n");
                return;
            default:
                printf("❌ Choix invalide. Veuillez réessayer.\n");
        }
    }
}


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
                            

