#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "modele.h"
// **************** variables exo 8 ***************************************
Entete1 ent;
F *fichier_tovc;
Tbloc8 buf;
int choix , choix2 , choix7 , i  , j=0 ,n1;
int trouv =0;
char nom[20], mode[20];

// **************** variables exo 7 ***************************************


char nom[20], mode[20];
  int val;

TObF *f;
// ***********************************************************************



int main()
{
         system("cls");
    printf("\n\n");
    printf("\t\t\t\t\t       %c%c%c    %c%c%c   %c%c%c\n",177,177,177,177,177,177,177,177,177);
    printf("\t\t\t\t\t      %c      %c       %c \n",177,177,177);
    printf("\t\t\t\t\t      %c%c%c%c    %c%c     %c \n",177,177,177,177,177,177,177);
    printf("\t\t\t\t\t      %c         %c    %c \n",177,177,177);
    printf("\t\t\t\t\t       %c%c%c   %c%c%c    %c%c%c\n\n",177,177,177,177,177,177,177,177,177);
    printf("\t\t\t\t\t   annee universitaire  2019-2020\n\n");
    printf ("\t  °°°°°°°° **********************  TP 02 SFSD  *************************  °°°°°°°°\n");
    printf ("\t  °°°°°°°°                                                                °°°°°°°°\n");
    printf ("\t  °°°°°°°°                       Realise par :                            °°°°°°°°\n");
    printf ("\t  °°°°°°°°             Noui Akram  / Belguenbour Walid                    °°°°°°°°\n\n\n\n");
    system("pause");
     do {
    system("cls");
    printf("\n\n\t\t  *********                    choix de l'exercice                         ********\n\n");

    printf("1) executer l'exercice 07\n");
    printf("2) executer l'exercice 08\n");
    printf("3) quitter le programme \n ");
    printf("\tchoix : ");
    scanf(" %d", &choix2);
    printf("\n---------------------------\n\n");

    switch(choix2) {
       case 2:{

         system("cls");

      //  Tbloc buf;
        printf("\n\n\t\t*********      exercice 08 / recherche dichotomique dans un fichier TOV/C      ******* \n\n\n\n");
        printf("Capacitee maximale des blocs = %d enregistrements\t", MAXTAB1);
        printf("\tLa cle est ecrite sur %d caracteres\n\n", MAXKEY );

        // Ouverture du fichier ...
        printf("Donnez le nom du fichier : ");
        scanf(" %s", nom);
        printf("Ancien ou Nouveau ? (a/n) : ");
        scanf(" %s", mode);
        if ( mode[0] == 'a' || mode[0] == 'A') {
       ouvrir1( nom , 'A' , &fichier_tovc);

       } else {
       ouvrir1( nom , 'N', &fichier_tovc);
        printf("\n");
          SetColor(10);
      	printf("\nChargement initial....\n");
      	getch();
      	SetColor(15);
      	printf("\n");
       chargement_initial1(&fichier_tovc);
              }


              // Menu principal ...
               do {
                  	printf("\n--------- M E N U ---------\n");
            	printf("1) Afficher l'entete du fichier\n");
            	printf("2) Recherche Dichotomique d'un enregistrement dans le fichier\n");
            	printf("3) Affichage de bloc(s)\n");
            	printf("0) Quitter le programme\n");
            	printf("\tchoix : ");
            	scanf(" %d", &choix);
            	printf("\n---------------------------\n\n");

            	switch(choix) {
            	   case 1:{
                   system("cls");
                 info1(fichier_tovc);
                 break;



                }
            	   case 2:{
                   int a1=0;
                    printf("Donnez la cle a rechercher : ");
                    scanf("%d", &n1);
                    a1 = RechercheDicho(fichier_tovc , n1 , &trouv , &i , &j );
                    printf("\n\n\t\tnombre d'acces physique genreres lors de la recherche :  %d\n\n\n\n\n" , a1);

                    system("pause");


                   break;


                 }
            	   case 3:{
                     system("cls");
                     Affichage_fichier(fichier_tovc);
                     system("pause");
                   break;
            	   }

            	}
               } while ( choix != 0);

                  fermer1(fichier_tovc);

                  break;
                }

       case 1:{


                                     // Ouverture du fichier ...
                       Sleep(100);
                       printf("                      **************************---EXO7---**************************\n");
                       Sleep(100);
                       printf("\n");
                       printf("Donnez le nom du fichier : ");
                       scanf(" %s", nom);
                       strcat(nom,".bin");
                       printf("Ancien ou Nouveau ? (a/n) : ");
                       scanf(" %s", mode);
                       if ( mode[0] == 'a' || mode[0] == 'A' )
                    	ouvrir( &f, nom , 'A');
                       else {
                    	ouvrir( &f, nom , 'N');
                        printf("\nDonnez le nombre d'enregistrement(s) que vous voulez charger dans le fichier: ");
                        char n[10] ;
                        scanf("%s",&n);
                        val=atoi(n);
                        if (val<=0)
                        {
                            printf("entree invalide ou fichier vide");
                            EXIT_FAILURE;
                        }
                        else
                        {
                        printf("\n");
                        SetColor(10);
                    	printf("\nChargement initial....\n");
                    	getch();
                    	SetColor(15);
                    	printf("\n");
                        Chargement(f,val);
                      }
                    }
                        //Chargement(n)


                                  system("cls");
                                  printf("\nLe fichier avant la reorganisation:\n");
                                  Afficher(f,nom);
                                  printf("\n");
                                  printf("\n\t Choisissez un pivot: ");
                        int x;
                        scanf("%d",&x);
                        printf("\n");
                        Reorganisation(f,x);
                        printf("Les valeurs en ");
                        SetColor(10);
                        printf("vert ");
                        SetColor(15);
                        printf("sont les valeurs inferieurs ou egales a la valeur pivot;\n");
                        getch();
                        printf("Les valeurs en ");
                        SetColor(20);
                        printf("rouge ");
                        SetColor(15);
                        printf("sont les valeurs superieurs a la valeur pivot;\n");
                        printf("\n");
                        getch();
                        printf("\nLe fichier apres la reorganisation:\n");
                        Afficher_bis(f,nom,x);
                        SetColor(15);
                        Sleep(100);
                        fermer(f);
                        printf("\n");
                        printf("\n                   **************************---FIN---**************************\n\n\n\n");
                                   system("pause");
                  break;
               }
            }
          }while (choix2 != 3);

    return 0;
}
