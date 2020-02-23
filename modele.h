#ifndef MODELE_H_INCLUDED
#define MODELE_H_INCLUDED
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXTAB 5
#define MAXTAB1 100
#define MAXKEY 10


//*************************************************** exo 8 *************************************************************************
typedef struct Tbloc8 //* structure d'un bloc
{
   char tab[512];
   int pos_libre ;
   char cle1[11] ;
   char cle2[11];

}
Tbloc8;

typedef struct Tbloc8 Buffer1 ;
typedef struct Entete1 {

	   long nb_db ;

	} Entete1;

typedef struct F
{
      FILE *file;
    Entete1 entete;
}
F ;

//// structures du semi enregistrement ------------------------------------------------------------------------------------------
typedef char Semi_enreg[MAXTAB1+1];  //// chaine de caractère qui contiendra l'information pour récup_chaine et écrire_chaine
typedef struct Enregistrement
{
    //// longueur de l'info => 3 caractères
    int cle ; /// 3 caractères
    int supp ; /// booleen : 3 caractères
    char info[MAXTAB1-14];
    /// la taille max de l'enregistrement est le bloc. ( 6 = taille longueur + taille clé + taille supp + 1)
}Enregistrement;

void aff_entete1(F*fp ,long val);
long entete1(F *fp);
void liredir1(F *fp, int i , Buffer1 *buf);
void ecriredir1(F*fp, int i, Buffer1 *buf);
void fermer1(F *f);
int  ouvrir1(char nom_fichier[], char mode , F**fp);
void Alloc_bloc(F* fichier);
void num_to_string(int num, int max, char * s);  // fonction qui tranforme un entier en chaine de characteres
void enreg_to_semi (Enregistrement en, Semi_enreg se);   // fonction qui transforme un struct en un enregistrement sous forme de char (Semi_enreg)
void semi_to_enreg (Semi_enreg se, Enregistrement * en); // fonction qui tranforme un enregistrement sous forme de chaine ( Semi_enreg) à un structs
void recuperer_se(F * fichier, int * j, Semi_enreg se , Tbloc8 buf);  // fonction qui recupere un enregistrement sous forme de char (Semi_enreg)
void copier_chaine(char * s, int i, int max, char * r);  /* permet de copier de la chaine s à partir de la position i,une sous chaine r de longueur max */
void chargement_initial1(F **fichier_tovc);    // permet de charger le fichier en entrant le nb d'enregistrement souhaité
void Affichage_fichier(F * fichier);
int RechercheDicho(F *f ,  int val, int *trouv, long *i, int *j ); // fonction de recherche dichotomique retourne le bloc , la position et le nb de lecture physiques
char *randstring(int length) ; // generer une chaine de caractere aleatoire a partir de la taille
void SetColor(int ForgC);



//*************************************************** exo 7 *************************************************************************
/*----      D�claration de la structure     ----*/

typedef struct Tenreg{
    int Eff;
    int cle;
    int info;
}Tenreg;

typedef struct Tbloc{
    Tenreg Tab[MAXTAB];
    int nb;                          //Nombre d'enregistrements ins�r�s dans le bloc
}Tbloc;
typedef struct Entete{
    int adrDerBloc;                 //Adresse du dernier bloc
    //On ajoute des caract�ristiques qui nous aideront lors de la manipulation
}Entete;
typedef struct TObF{
    FILE *fichier;
    Entete entete;
}TObF;

/*----      FONCTIONS       ----*/
int ouvrir(TObF **f,char *chemin,char mode);
void fermer(TObF *f);
void lireDir(TObF*f, int NBloc, Tbloc *buffer);
void ecrirDir(TObF *f,int NBloc, Tbloc *buffer);
int entete(TObF *f, int i );
void aff_entete(TObF *f, int i, int val);
int alloc_bloc(TObF *f);
int Random();
//void Chargement(int i);
void Chargement(TObF *f,int i);
void Afficher(TObF *f,char *path);
//void Afficher(char *path);
void SetColor(int ForgC);
void Afficher_bis(TObF *f,char *path,int vp);
void Reorganisation (TObF *f,int vp);
















#endif // MODELE_H_INCLUDED
