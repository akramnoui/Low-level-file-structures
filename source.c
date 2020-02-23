#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "modele.h"

//*************************************************** exo 8 *************************************************************************
//*************************************************************************************************************************************
//***********************************************************************************************************************************

void aff_entete1(F*fp ,long val)
{
       fp->entete.nb_db=val;

   }
   //*********************************************************************
long entete1(F *fp)
{
 return(fp->entete.nb_db);

}
//*********************************************************************
void liredir1(F *fp, int i , Buffer1 *buf)
{
   if(i <= entete1(fp))
   {
       fseek(fp->file,(sizeof(Entete1)+sizeof(Tbloc8)*(i-1)),SEEK_SET); // positionnement au debut du bloc numero i
       fread(buf,sizeof(Buffer1),1,fp->file);                         //lecture d'un bloc de caract�re correspondant a la taille du bloc dans le buffer
       rewind(fp->file);
   }
                                        // repositionnement endebut de fichier

}

//**********************************************************************
void ecriredir1(F*fp, int i, Buffer1 *buf)
{

     fseek(fp->file,sizeof(Entete1)+sizeof(Tbloc8)*(i-1),SEEK_SET);
     fwrite(buf,sizeof(Buffer1),1,fp->file);

}
//***********************************************************************
void fermer1(F *f)
{

    rewind(f->file);
    fwrite(&(f->entete), sizeof(Entete1), 1, f->file);
    fclose(f->file);
    free(f);
}
//***********************************************************************
int  ouvrir1(char nom_fichier[], char mode , F**fp)
{

    *fp=malloc(sizeof(F));                      // allocation  de la structure
    Buffer1 buf;
    if( (mode=='A') ||  (mode == 'a') )
    {
        (*fp)->file=fopen(nom_fichier ,"rb+");
        if ((*fp)->file != NULL)
        {
            fread(&((*fp)->entete),sizeof(Entete1),1,(*fp)->file);
            return 1;
        }
        else return 0;
    }
    else
    {
        if( (mode=='N') ||  (mode == 'n') )
        {
             (*fp)->file=fopen(nom_fichier,"wb+");
             if ((*fp)->file != NULL)
             {
             aff_entete1(*fp,0);
             fwrite(&((*fp)->entete),sizeof(Entete1),1,(*fp)->file);
             sprintf(buf.tab,"%s","");
             ecriredir1(*fp,1,&buf);
             return 1;
             }
             else return 0;


        }
        else
        {
            printf("format d'ouverture impossible");
            return 0;
        }
    }
    printf("file opened");
  //************************************************************************************


}
void num_to_string(int num, int max, char * s)  // fonction qui tranforme un entier en chaine de characteres
{
    char s_num[MAXKEY];

    sprintf(s_num,"%d",num);

    int j = max - strlen(s_num) ;
    sprintf(s,"%s","");
    while (j > 0) {sprintf(s,"%s0",s);j--;}
    sprintf(s,"%s%s",s,s_num);
}

  //************************************************************************************


void enreg_to_semi (Enregistrement en, Semi_enreg se)   // fonction qui transforme un struct en un enregistrement sous forme de char (Semi_enreg)
{
  char chaine[4];
  int taille = strlen(en.info) + MAXKEY+4;


  sprintf(se,"%s","");

  /// écriture de la taille de l'info dans le semi enregistrement
  num_to_string(taille,3,chaine);
  sprintf(se,"%s%s",se,chaine);
  /// écriture du booléen supp
  num_to_string(en.supp,1,chaine);
  sprintf(se,"%s%s",se,chaine);

  /// écriture de la clé dans le semi enregistrement
  num_to_string(en.cle,MAXKEY,chaine);
  sprintf(se,"%s%s",se,chaine);

  /// écriture de l'info
  sprintf(se,"%s%s",se,en.info);
}
//************************************************************************************


void semi_to_enreg (Semi_enreg se, Enregistrement * en) // fonction qui tranforme un enregistrement sous forme de chaine ( Semi_enreg) à un structs
{
    char chaine[MAXTAB1+1];

    /// la clé
    sprintf(chaine,"%s","");
    copier_chaine(se,4,MAXKEY,chaine);
    en->cle = atoi(chaine);
    /// le booleen
    sprintf(chaine,"%c",se[3]);
    en->supp = atoi(chaine);

    ///l'info
    copier_chaine(se,MAXKEY+4,strlen(se)-(MAXKEY+3),en->info);

}
  //************************************************************************************

void recuperer_se(F * fichier, int * j, Semi_enreg se , Tbloc8 buf)  // fonction qui recupere un enregistrement sous forme de char (Semi_enreg)
{

    char taille[4]; /// contiendra la taille de l'info
    int k ;
    sprintf(taille,"%s","");
    sprintf(se,"%s","");
  //  printf("le buffer  recupere est %s\n\n " , buf.tab);

    /// récuperation de la taille de l'info, int dans taille, char dans se
    for (k=0; k<3; k++)
    {
            sprintf(taille,"%s%c",taille,buf.tab[*j]);
            sprintf(se,"%s%c",se,buf.tab[*j]);
            (*j)++;

    }

    /// recuperation de la clé, le booléen et l'info dans la variable se
    for (k=0; k<(atoi(taille) - 3 ); k++)
    {
         sprintf(se,"%s%c",se,buf.tab[*j]) ;
         (*j)++;
    }
  //************************************************************************************

}
void copier_chaine(char * s, int i, int max, char * r)  /* permet de copier de la chaine s à partir de la position i,une sous chaine r de longueur max */
{
   /// if (i < 0 ) i = 0 ;
   sprintf(r,"%s","");
   while (i<strlen(s) && max>0)
   {
       sprintf(r,"%s%c",r,s[i]);
       i ++ ;
       max -- ;
   }
}
//**********************************************************************************************************************************

void chargement_initial1(F **fichier_tovc)    // permet de charger le fichier en entrant le nb d'enregistrement souhaité
{
  int i , k , val , taille  ,key1;
  int j  ;
  Enregistrement en;
  Semi_enreg se;
  char *s_info;
  Tbloc8 buf;
  i = 1;
  j = 0;
  printf("Donnez le nombre d'enregistrement a inserer : ");
  char n[MAXKEY] ;
    scanf("%s",&n);
    val=atoi(n);
    if (val<=0)
    {
        printf("entree invalide ou fichier vide");
        EXIT_FAILURE;
    }
    else
    {
  srand(time(0));
  sprintf(buf.tab , "%s","");

  for ( k = 0 ;  k < val ; k ++)
  {
    // genrerer un enregistrement
    en.cle = k*10;
    en.supp = 0;
    taille = rand() % 50;
    s_info = randstring(taille-(MAXKEY+4));
    sprintf(en.info , "%s" , s_info);
    sprintf(se , "%s" ,"");
    enreg_to_semi(en , se);       // transformer un enregistrement en char
    taille = strlen(se);
    j = j + taille;               // calcul de la position
    if (j <= MAXTAB1)
    {
      key1 = atoi(buf.cle1);
      if (en.cle <= key1){ sprintf(buf.cle1 , "%d" ,  en.cle);} // maj cle1
      sprintf(buf.tab , "%s%s" , buf.tab , se);
      buf.pos_libre = j; // sauvegarde de la derniere position
    }else{
       // mise a jour de la position libre
      ecriredir1(*fichier_tovc, i, &buf);
      i ++;
      sprintf(buf.tab , "%s","" );  // ecriture dans un nv bloc
      sprintf(buf.cle1 ,"%d", en.cle);
      sprintf(buf.tab ,"%s%s" ,buf.tab,se);
      j =  taille;
      }
        sprintf(buf.cle2 , "%d"  , en.cle);
    }
    // derniere ecriture
      buf.pos_libre = j ;
      ecriredir1(*fichier_tovc , i , &buf);
      //m-a-j de l'entete
      aff_entete1(*fichier_tovc , i) ;
    }

    }

/********************************************************************************************************************/

void Affichage_fichier(F * fichier)
{
    int i = 1  ;
    long ndb;
    int j = 0;
    Enregistrement en ;
    Semi_enreg se ;
    Tbloc8 buf;
    char  key[MAXKEY] ;
      sprintf(buf.tab , "%s" , "");
    SetColor(10);
    printf("\n\n -----------------------------------       Les enregistrements       ---------------------------------------\n\n");
    ndb = entete1(fichier);
    while (i <= ndb)
    {

      sprintf(buf.tab , "%s" , "");
      liredir1(fichier,i,&buf);
       SetColor(20);
       printf("\n\n\t\t***********************************  bloc %d ************************************\n", i);
       SetColor(10);
         printf("\n\t\t\t|length\t| key\t| info\n");
        SetColor(15);
           j = 0;

      while ( j < buf.pos_libre)
      {
         sprintf(se , "%s" , "");
         recuperer_se(fichier,&j,se,buf);
         semi_to_enreg(se,&en);
          num_to_string(en.cle,MAXKEY,key);
         printf("\n\n\t\t\t|  %d\t|  %s\t| %s " ,strlen(se),key,en.info);
     }
     i++;

       if ((i > ndb) && (j == buf.pos_libre)) break ;
   }
    printf("\n\n");
  }
/********************************************************************************************************************/
      int RechercheDicho(F *f ,  int val, int *trouv, long *i, int *j ) // fonction de recherche dichotomique retourne le bloc , la position et le nb de lecture physiques
{
   long bi, bs, cpt;
   int stop, inf, sup , key1 , key2 , cpt2=0;
   Enregistrement en;
   Semi_enreg se;
   Tbloc8 buf;
   *j = 0;

   bi = 1;
   bs = entete1(f);
   *trouv = 0;
   stop = 0;
   cpt = 0; // compteur de lectures physiques
   while ( bi <= bs && !*trouv && !stop ) {
      	*i = (bi + bs) / 2;		// le milieu entre bi et bs
      	liredir1( f, *i, &buf ); cpt++; 	// lecture du bloc du milieu
        key1 = atoi(buf.cle1);
        key2 = atoi(buf.cle2);
      	if ( val < key1 )
      	   bs = *i - 1;		// la recherche contiue dans la 1ere moitie

      	else
      	   if ( val > key2 )
      	      	bi = *i + 1;	// la recherche contiue dans la 2eme moitie
      	   else if ( (val <= key2) && (val >= key1) ) {
             // recherche à l'interieur du bloc (sequentielle)
               while (*j < MAXTAB1 && !*trouv  && en.cle < val ){
                   cpt2++;
                   recuperer_se(f, &(*j), se , buf);  // recupereation de l'enregistrement en char
                   semi_to_enreg(se,&en); // transformation en struct
                   if (en.cle == val && en.supp == 0 ){
                     *trouv = 1 ;

                    }
                 }
                    stop = 1;
                    *j = (*j) - strlen(se); // retour au debut de l'enregistremetn pour retourner la postion

             }
             if ( bi > bs ) {
           *i = bi;
           *j = 0;
             }
    }
    if (!*trouv){
      // cas cle non existante
      if (val > buf.cle2) i++;
        SetColor(20);
        printf("\n\n\t\t**********  la cle recherche n'existe pas  ********** \n\n");
        SetColor(15);
        printf("\n\t\tl'enregistrement doit etre eventuellement insere au :");
         printf("\n\n\t\t|rang  : %d\t|bloc  : %d\t|position  : %d", cpt2, *i , *j );

    }else{
      // si cle existante
        printf("\n\tAffichage de l'enregistrement : \n\n");
        printf("\t\t|length    %ld\t|key     %ld\t|info      %s\n",strlen(se),en.cle,en.info);
        printf("\n\tinformations sur l'enregistrement   :");
        SetColor(10);
         printf("\n\n\t\t|rang  : %d\t|bloc  : %d\t|position  : %d", cpt2, *i , *j );
         SetColor(15);

    }
   return cpt;

}

void info1(F *f)
{
  int n = entete1(f);
  SetColor(10);
  printf("\n\t\t\t**********  votre fichier comporte  %d  blocs  **********\n\n " , n);
  SetColor(15);
}


//******************************************************************************************************************
char *randstring(int length) {  // genere une une chaine de caractere  aleatoire pour servir d'info
    static int mySeed = 25011984;
    char *string = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789,.-#'?&^{|=<>:~%§/}!";
    size_t stringLen = strlen(string);
    char *randomString = NULL;

    srand(time(NULL) * length + ++mySeed);

    if (length < 1) {
        length = 1;
    }

    randomString = malloc(sizeof(char) * (length +1));

    if (randomString) {
        short key = 0;

        for (int n = 0;n < length;n++) {
            key = rand() % stringLen;
            randomString[n] = string[key];
        }

        randomString[length] = '\0';

        return randomString;
    }
    else {
        printf("No memory");
        exit(1);
    }
}

//******************************************************************************************
    void SetColor(int ForgC)
 {
     WORD wColor;

      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO csbi;


     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {

          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
 }





 //*************************************************** exo 7 *************************************************************************
 //*************************************************************************************************************************************
 //***********************************************************************************************************************************



 TObF *f;

 /************************************************MACHINE ABSTRAITE*********************************************/

 /*--------------Fonction d'ouverture d'un fichier--------------*/

 int ouvrir(TObF **f,char *chemin,char mode)
 //mode indique si c'est un nouveau ou un ancien fichier
 {
     *f = malloc(sizeof(TObF));
     char s[3];
     if((mode == 'A') || (mode == 'a')) sprintf(s,"rb+");
     else if ((mode == 'N') || (mode == 'n')) sprintf(s,"wb+");
     else return 0;
     (*f)->fichier = fopen(chemin, s);
     if((*f)->fichier == NULL)   return 0;
     if((mode == 'A') || (mode == 'a'))
         {
             fread(&((*f)->entete), sizeof(Entete), 1, (*f)->fichier);
         }
         else if ((mode == 'N') || (mode == 'n'))
             {        (*f)->entete.adrDerBloc = 0;
             }
     return 1;

 }


 /*--------------Fonction de fermeture d'un fichier--------------*/
 void fermer(TObF *f)
 {
      //Sauvegarde de l'ent�te
     rewind(f->fichier); //Se positionner au debut du ficheir
     fwrite(&(f->entete), sizeof(Entete), 1, f->fichier);
     fclose(f->fichier);
     free(f);
 }

 /*-----------------Fonction de lecture d'un bloc----------------*/
 void lireDir(TObF *f,int N_Bloc,Tbloc *buffer)
 {
     if(N_Bloc <= (f->entete).adrDerBloc)
         {
             fseek(f->fichier, sizeof(Entete) + (N_Bloc-1) * sizeof(Tbloc),SEEK_SET); //se positionner exactement au d�but du bloc num�ro N_Bloc
             fread(buffer, 1, sizeof(Tbloc), f->fichier);
         }
 }


 /*-----------------Fonction d'�criture d'un bloc----------------*/
 void ecrireDir(TObF *f,int N_Bloc,Tbloc *buffer)
 {
     if(N_Bloc <= (f->entete).adrDerBloc)
         {
             fseek(f->fichier, sizeof(Entete) + (N_Bloc-1) * sizeof(Tbloc),SEEK_SET);   //se positionner exactement au d�but du bloc num�ro N_Bloc
             fwrite(buffer, 1, sizeof(Tbloc), f->fichier);
         }
 }

 /*-----Fonction de recuperation des informations de l'entete---*/

 int entete(TObF *f,int i)
 {
     if(i == 1) return (f->entete).adrDerBloc;
     else return -1;

 }

 /*-------------Fonction de modification de l'ent�te-------------*/
 void aff_entete(TObF *f, int i, int val)
 {
     if(i == 1) (f->entete).adrDerBloc = val;
 }

 /*--------------------L'allocation d'un bloc--------------------*/
 int alloc_bloc(TObF *f)
 {
     aff_entete(f,1,entete(f,1)+1);  //modifier l'adresse du dernier bloc dans l'ent�te
     return entete(f,1);
 }
 /*----------------------Chargement initial---------------------*/

 void Chargement(TObF *f,int i)
 {
     Tbloc  buf;
     int N_blocs;
     int k,j,a,b,x;
     a = i / MAXTAB ;
     b = i % MAXTAB ;
     j = 0;
     if ( b>0 ) //le dernier bloc peut ne pas �tre rempli compl�tement
     {
     x = a + 1; //nombre de blocs n�cessaires pour le chargement
     for (j=1;j<x+1;j++)
     {
         N_blocs=alloc_bloc(f);
         if (j < x) //dernier bloc pas encore atteint
             {
                 for (k=0;k<MAXTAB;k++) //tous les blocs sont de taille MAXTAB
                     {
                         buf.Tab[k].cle=Random();
                         buf.Tab[k].Eff=0;
                     }
                     buf.nb=MAXTAB;
             }else if (j == x ) // b est la taille du dernier bloc
             {
                     for (k=0;k<b;k++)
                 {
                     buf.Tab[k].cle=Random();
                     buf.Tab[k].Eff=0;
                 }
                 buf.nb=b;
             }

             ecrireDir(f,N_blocs,&buf);

     }
     } else //MAXTAB est la taille de tous les blocs
     {
         x = a; //x le nombre de blocs n�cessaires pour le chargement initiale

         //printf("  %d  ",(f->entete).adrDerBloc);
         srand( time( NULL ));
         for (j=1;j<x+1;j++)
     {
         N_blocs=alloc_bloc(f);
        for (k=0;k<MAXTAB;k++)
             {
                 buf.Tab[k].cle=Random();
                 buf.Tab[k].Eff=0;
             }
         buf.nb=MAXTAB;

         ecrireDir(f,N_blocs,&buf);
     }
     }
     ((f->entete).adrDerBloc)=x; //mise � jour de l'adresse du dernier bloc
     printf(" Le nombre de blocs est de '%d'  \n",(f->entete).adrDerBloc);
     printf("\n");
     getch();
     SetColor(10);
     printf("Fin de chargement....\n");
     getch();
     SetColor(15);
 }


 /*----      Afficher contenu du fichier ----*/
 void Afficher(TObF *f,char *path)
 {
     Tbloc  buf;
    // TObF *f=NULL;
     //ouvrir(&f,path,'A');
     int k=1 ;
     printf(" Entete: %d  ",(((f)->entete).adrDerBloc));
     while (k <= (((f)->entete).adrDerBloc))  //f->entete
     {
         //pour chaque bloc
     lireDir(f,k,&buf);
     printf("\nBloc n : %d :\n ",k);
     int i;
     for (i=0;i<buf.nb;i++)
         {
             //on affiche la cl� de chaque enregistrement
             if (buf.Tab[i].Eff==0){
             printf("[%d]",buf.Tab[i].cle);}

         }
         k++;
     }
   // fermer(f);
 }

 /*----      Focntion pour les couleurs----*/

  /*----      Afficher contenu du fichier apr�s r�organisation ----*/
 void Afficher_bis(TObF *f,char *path,int vp)
 {
     Tbloc  buf;
    // TObF *f=NULL;
     //ouvrir(&f,path,'A');
     int k=1 ;
     printf(" Entete: %d  ",(((f)->entete).adrDerBloc));
     while (k <= (((f)->entete).adrDerBloc))  //f->entete
     {
         //pour chaque bloc
     lireDir(f,k,&buf);
     SetColor(15);
     printf("\nBloc n : %d :\n ",k);
     int i;
     for (i=0;i<buf.nb;i++)
         {
             //on affiche la cl� de chaque enregistrement
             if (buf.Tab[i].Eff==0){
             	if(buf.Tab[i].cle<=vp)
             	{
             		SetColor(10);
             		printf("[%d]",buf.Tab[i].cle);
 				}
 				else
 				{
 					SetColor(20);
 					printf("[%d]",buf.Tab[i].cle);
 				}
             }

         }
         k++;
     }
   // fermer(f);
 }

 /*----      g�n�rer al�atoirement  ----*/
 int Random(){
     int number;
     //time_t t;
     //srand((unsigned) time(&t));
     number = rand() % 200;
     return number;
 }
 /*------------------------------------LA REORGANISATION------------------------------------*/
 void Reorganisation (TObF *f,int vp)
 {
     Tbloc buf1 , buf2;
     int adr1 , adr2,j, trouv = 0,i ,equal =0, ind1 , ind2 , trouv2 = 0 , inter , fin = 0,cle , test = 0;
     //en utilisant 2 buffers buf1 et buf2 on parcourt notre fichier du premier bloc � l'aide de buf1 et on incr�mente et � partir du dernier bloc et on d�cr�mente jusqu'� ce qu'on est buf1=buf2
     adr1 = 1;
     adr2 = entete(f,1);
     i=0; //parcours de buf1
     j = 0 ;//parcours de buf2
     lireDir(f,adr1,&buf1);//r�cup�ration des deux buffers buf1 et buf2
     lireDir(f,adr2,&buf2);
     while ((adr1 <= adr2) && (fin == 0))
     {
         i = 0;
         //deux cas distincts
         if (adr1 == adr2){equal = 1;}
        while ((i<buf1.nb) && (equal == 0)) //si les 2 blocs sont distincts
        {
            trouv = 0;//pour chaque bloc de la premiere partie du fichier on teste s'il existe un enreg qui a une cl� > VP
            if (buf1.Tab[i].cle > vp)
            {
                //si c'est le cas
              while ((trouv == 0) && (equal == 0))
              {
                  if (buf2.Tab[j].cle <= vp ) //on cherche dans la deuxi�me partie du fichier s'il existe un enreg qui a un� cl� <= VP
                  { //lorsqu'on trouve cet enreg on fait une permutation
                     cle = buf1.Tab[i].cle;
                     buf1.Tab[i].cle = buf2.Tab[j].cle;
                     buf2.Tab[j].cle = cle;
                     trouv = 1 ;
                  } ;
                  j++ ;
                  if (j == buf2.nb) //apr�s chaque incr�mentation on teste si on est arriv� a la fin du bloc
                  {
                      //si c'est le cas on fait une �criture et on r�cup�re un autre bloc
                      j = 0 ;
                      ecrireDir(f,adr2,&buf2);
                      adr2 -- ;
                      lireDir(f,adr2,&buf2);
                  };
                 if (adr1 == adr2){equal = 1; test = 1;} //on v�rifie si les num�ros des blocs sont �gaux car si le cas on fera un autre traitement
                 //"test" c'est pour savoir si c'est le dernier changement dans le bloc qui est entre les deux parties du fichier
              };

            };
              i ++ ;
        };
        if (adr1 != adr2) //si adr1 != adr2 on �crit buf1 et on lit le prochain bloc
             {
                 ecrireDir(f,adr1,&buf1);
                 adr1 ++ ;
                 lireDir(f,adr1,&buf1);
             };
        if (adr1 == adr2) //le cas du bloc au milieu
        { //on parcourt le bloc avec 2 indices ind1 du premier indice et on incr�mente, ind2 du dernier indice et on d�cr�mente jusqu'� ce que ind1=ind2
            ind1 = 0;
            ind2 = buf1.nb-1;
     if (test == 1) // si le dernier changement concernant ce bloc �tait fait dans buf1
            { //on fait le traitement en utilisant buf1
            while (ind1 < ind2)
     {
        if (buf1.Tab[ind1].cle > vp)
            {
                trouv2 = 0;
                while ((trouv2 == 0) && (ind1 < ind2))
                {
                    if (buf1.Tab[ind2].cle <= vp)
                    {
                        inter = buf1.Tab[ind1].cle;
                        buf1.Tab[ind1].cle =buf1.Tab[ind2].cle;
                        buf1.Tab[ind2].cle = inter ;
                        trouv2 = 1;
                    };
                    ind2 -- ;
                };
            };
            ind1 ++ ;
     };
            ecrireDir(f,adr2,&buf1);
            fin = 1;
        }else
        {
          //on fait le m�me traitement mais en utilisant buf2
          while (ind1 < ind2)
     {
        if (buf2.Tab[ind1].cle > vp)
            {
                trouv2 = 0;
                while ((trouv2 == 0) && (ind1 < ind2))
                {
                    if (buf2.Tab[ind2].cle <= vp)
                    {
                        inter = buf2.Tab[ind1].cle;
                        buf2.Tab[ind1].cle =buf2.Tab[ind2].cle;
                        buf2.Tab[ind2].cle = inter ;
                        trouv2 = 1;
                    };
                    ind2 -- ;
                };
            };
            ind1 ++ ;
     };
            ecrireDir(f,adr2,&buf2);
            fin = 1;
        }  ;
        };
     };

 }

//****************************************************************************

//******************************************************************************
