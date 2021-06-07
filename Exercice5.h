#include"Exercice4.h"
#include "API_Grille.h"
#include "API_Gene_instance.h"

typedef struct {
    int dim;
    int nbcl;

    Cellule_som* Lzsg;
    Cellule_som** B;
    int* tab_taille;

} Somme_Zsg;


void init_Somme_Zsg(int dim,int nbcl,Somme_Zsg* Zone);

void ajoute_Somme_Zsg(Sommet* s, Somme_Zsg* Zone);

void ajoute_Somme_Bordure(Sommet* s, Somme_Zsg* Zone);

void afficher_sommet ( Sommet* s);

void afficher_liste_sommet(Somme_Zsg* Zone, int color);

void afficher_Lzsg(Somme_Zsg* Zone);

int appartient_Somme_Zsg(Sommet* s, Somme_Zsg* Zone);

int appartient_Somme_Bordure(Sommet* s, Somme_Zsg* Zone);


void maj(Somme_Zsg* Zone,int color,int aff,Grille *G);

int bordure_vide(Somme_Zsg* Zone);

int max_bordure( int** M, Grille* G,int dim, int nbcl, int aff );

void affichage_jeu(Graphe_zone* Gz, int dim);


void detruire_Somme_Zsg(Somme_Zsg* Zone);
