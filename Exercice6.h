#include"Exercice5.h"


typedef struct cellule_som2 {
 Sommet * sommet ;
 struct cellule_som2 * suiv ;
 struct cellule_som2 * prec ;
} Cellule_som2 ;

typedef struct _fileSommet {
    Cellule_som2 * tete;
    Cellule_som2 * queue;
    int nb;
} File_Sommet;


void initFile(File_Sommet *F);

int File_vide(File_Sommet *F);

int enfiler(File_Sommet *F, Sommet *s);

Sommet *defiler(File_Sommet *F);

void parcours_largeur( Graphe_zone* Gz,Sommet* s1);

Cellule_som* trouver_parcours(Graphe_zone* Gz,Sommet* s1 , Sommet* s2);

int jeu_strategie(int **M,Grille* G, int dim, int nbcl, int aff);
