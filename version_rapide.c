#include<stdio.h>
#include"version_rapide.h"
#include <unistd.h>


void init_Zsg(int dim,int nbcl,S_Zsg* Zone){
    Zone -> dim = dim;
    Zone -> nbcl = nbcl;

    init_liste(&(Zone->Lzsg));

    Zone -> B = (ListeCase *)malloc(nbcl * sizeof(ListeCase));

    int j;
    for(j=0;j<nbcl;j++){
        init_liste((Zone->B)+j);
    }

    Zone -> App = (int **) malloc(dim * sizeof(int *));
    int i;
    int ** tmp = Zone -> App;

    for(i=0;i<dim;i++){
        tmp[i]= (int*) malloc (dim * sizeof(int ));
        for(j=0;j<dim;j++){
            tmp[i][j]=-2;
        }
    }

}

void ajoute_Zsg(int i, int j, S_Zsg* Zone){

    ajoute_en_tete(&(Zone->Lzsg),i,j);
    int** tmp = Zone-> App;
    tmp[i][j]=-1;

}

void ajoute_Bordure(int i, int j, int cl, S_Zsg* Zone){

    ajoute_en_tete((Zone->B)+cl,i,j);
    int** tmp = Zone-> App;
    tmp[i][j]=cl;

}

int appartient_Zsg(int i, int j, S_Zsg* Zone){
    return (Zone->App[i][j]==-1);
}


int appartient_Bordure(int i, int j,int cl, S_Zsg* Zone){
    return (Zone->App[i][j]==cl);
}


int agrandit_Zsg(int** M, S_Zsg* Zone, int color, int i, int j){

    ListeCase P;
    init_liste(&P);
    int k,l;
    int nbcase=Zone->dim;
    int taille=0;

    if(!appartient_Zsg(i,j,Zone)){
      ajoute_Zsg(i,j,Zone);
      taille++;
    ajoute_en_tete(&P,i,j);
}

    while(!test_liste_vide(&P)){

        enleve_en_tete(&P,&k,&l);

      if (k != 0){

          if (M[k-1][l]==color){
              if(!appartient_Zsg(k-1,l,Zone)){
                ajoute_Zsg(k-1,l,Zone);
                taille++;
                ajoute_en_tete(&P,k-1,l);
            }
          }

          else {
              int cl=M[k-1][l];
              if (!appartient_Bordure(k-1,l,cl,Zone)){
                ajoute_Bordure(k-1,l,cl,Zone);
            }

          }
      }


      if (k != nbcase-1){

          if (M[k+1][l]==color){
              if(!appartient_Zsg(k+1,l,Zone)){
                ajoute_Zsg(k+1,l,Zone);
                taille++;
                 ajoute_en_tete(&P,k+1,l);
            }

          }
          else {
              int cl=M[k+1][l];
              if (!appartient_Bordure(k+1,l,cl,Zone))
                ajoute_Bordure(k+1,l,cl,Zone);

          }
    }


      if (l != 0){

          if (M[k][l-1]==color){
              if(!appartient_Zsg(k,l-1,Zone)){
                ajoute_Zsg(k,l-1,Zone);
                taille++;
                ajoute_en_tete(&P,k,l-1);
            }


          }
          else {
              int cl=M[k][l-1];
              if (!appartient_Bordure(k,l-1,cl,Zone))
                ajoute_Bordure(k,l-1,cl,Zone);

          }
      }


      if (l != nbcase-1){

          if (M[k][l+1]==color){
              if(!appartient_Zsg(k,l+1,Zone)){
                ajoute_Zsg(k,l+1,Zone);
                taille++;
                 ajoute_en_tete(&P,k,l+1);
            }


          }
          else {
              int cl=M[k][l+1];
              if (!appartient_Bordure(k,l+1,cl,Zone))
                ajoute_Bordure(k,l+1,cl,Zone);
          }

      }

    }
    return taille;
}



int sequence_aleatoire_rapide(int** M, Grille* G,int dim ,int nbcl, int aff){
	int cpt=0;
    int i,j,nbcase,coul;
    int testfin=0;
	ListeCase tmp;

	nbcase=dim*dim;

	S_Zsg zone;
	init_Zsg(dim,nbcl,&zone);

	testfin+=agrandit_Zsg(M,&zone,M[0][0],0,0);

	while(testfin!=nbcase){
		cpt++;

		do {
			coul=rand()%nbcl;
		}while(coul==M[0][0]);

		tmp=zone.Lzsg;
		while(tmp!=NULL){
			M[tmp->i][tmp->j]=coul;
			tmp=tmp->suiv;
		}

		tmp=zone.B[coul];

		while(tmp!=NULL){
			testfin+=agrandit_Zsg(M,&zone,coul,tmp->i,tmp->j);
			tmp=tmp->suiv;
		}

		detruit_liste(&(zone.B[coul]));

		if(aff==1){
			for(i=0;i<dim;i++)
				for(j=0;j<dim;j++){
					Grille_attribue_couleur_case(G,i,j,M[i][j]);
				}

				Grille_attente_touche();
				Grille_redessine_Grille(G);


		}
    }
     detruire_Zsg(&zone);
    return cpt;
}



void detruire_Zsg(S_Zsg* Zone){

    detruit_liste(&(Zone->Lzsg));
    int i;
    for(i=0;i<Zone->nbcl;i++){
        detruit_liste(&(Zone->B[i]));
    }
    free(Zone->B);
     for(i=0;i<Zone->dim;i++){
        free(Zone->App[i]);
    }

     free(Zone->App);

}
