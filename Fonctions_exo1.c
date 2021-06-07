#include<stdio.h>
#include "Entete_Fonctions.h"
#include<time.h>

void trouve_zone_rec(int **M, int nbcase, int i, int j, int *taille, ListeCase *L){

ajoute_en_tete(L, i, j);
(*taille)++;
int couleur = M[i][j];
 M[i][j]=-1;

if ( j !=nbcase-1 && M[i][j+1]==couleur )

	trouve_zone_rec(M, nbcase,  i, j+1, taille, L);

if ( j != 0 && M[i][j-1]==couleur )
	trouve_zone_rec(M, nbcase,  i, j-1, taille, L);

if (i!=nbcase-1 && M[i+1][j]==couleur )

	trouve_zone_rec(M, nbcase,  i+1, j, taille, L);

if (i != 0 && M[i-1][j]==couleur)

	trouve_zone_rec(M, nbcase,  i-1, j, taille, L);


}




int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff){
	int cpt=0;
	int couleur = M[0][0] ;
	int tirage =M[0][0];
	ListeCase L;
	Elnt_liste *tmp ;
	init_liste(&L);
	int taille = 0;
	int access = 1;
	int nbcases=dim*dim;
	while(access){
		trouve_zone_rec(M, dim, 0, 0, &taille, &L);

		if(taille==nbcases)break;//c'est plus optimale afin d'eviter un dernier trouve_zone_rec

		while(couleur == tirage){

			couleur = rand()%(nbcl);
		}

		cpt++;
		tmp=(L);
		while(tmp){
			M[tmp->i][tmp->j]=couleur;
			tmp=tmp->suiv;
		}
		if(aff==1){
			tmp = (L);
			while(tmp){
				Grille_attribue_couleur_case(G, tmp->i, tmp->j ,couleur);
				tmp=tmp->suiv;
				}

			Grille_attente_touche();
			Grille_redessine_Grille(G);
		}
		tirage =M[0][0];
		taille=0;
		detruit_liste(&L);

	}
	detruit_liste(&L);
	detruit_liste(&tmp);
 	return cpt;

}



