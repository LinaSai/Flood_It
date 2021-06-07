
#include"Liste_case.h"

typedef struct sommet Sommet ;

/* Element d’une liste cha\^in\’ee de pointeurs sur Sommets */
typedef struct cellule_som {
Sommet * sommet ;
 struct cellule_som * suiv ;
} Cellule_som ;


struct sommet {
 int num ; /* Numero du sommet (sert uniquement a l’affichage) */
 int cl ; /* Couleur d’origine du sommet-zone */
 ListeCase cases ; /* Listes des cases du sommet-zone */
 int nbcase_som ; /* Nombre de cases de cette liste */
 int marque;

 int distance;
 Sommet* pere;

 Cellule_som * sommet_adj ; /* Liste des ar\eteses pointeurs sur les sommets
adjacents */
 };


 typedef struct graphe_zone {
 int nbsom ; /* Nombre de sommets dans le graphe */
 Cellule_som * som ; /* Liste chainee des sommets du graphe */
 Sommet *** mat ; /* Matrice de pointeurs sur les sommets indiquant
a quel sommet appartient une case (i,j) de la grille */
 } Graphe_zone;

void init_cellule(Cellule_som** L);

int est_vide(Cellule_som** L);

int ajoute_liste_sommet(Cellule_som** L, Sommet* S);

void detruit_liste_sommet(Cellule_som** L);

void ajoute_voisin(Sommet* s1, Sommet* s2);

int adjacents(Sommet* s1, Sommet* s2);

void creer_graphe_zone(Graphe_zone* Gz, int dim, int** M);

void affichage(Graphe_zone* Gz, int dim);

void detruire_sommet(Sommet* s);

void detruire_graphe_zone(Graphe_zone* Gz, int dim );
