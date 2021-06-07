#include<stdio.h>
#include"exercice2.h"

void trouve_zone_imp(int** M, int nbcase, int i, int j, int* taille, ListeCase* L){

    ListeCase P;
    init_liste(&P);
    int a,b;

    int color=M[i][j];

    ajoute_en_tete(&P,i,j);
    ajoute_en_tete(L,i,j);
    M[i][j]=-1;


    *taille=0;



    while(!test_liste_vide(&P)){

        enleve_en_tete(&P,&a,&b);
        //printf("depile %d %d \n",a,b);
        (*taille)++;

      if ((a != 0)&&(M[a-1][b]==color)){

          ajoute_en_tete(&P,a-1,b);
          ajoute_en_tete(L,a-1,b);
          M[a-1][b]=-1;
      }


      if ((a != nbcase-1)&&(M[a+1][b]==color)){

          ajoute_en_tete(&P,a+1,b);
          ajoute_en_tete(L,a+1,b);
          M[a+1][b]=-1;

      }


      if ((b != 0)&&(M[a][b-1]==color)){

          ajoute_en_tete(&P,a,b-1);
          ajoute_en_tete(L,a,b-1);
          M[a][b-1]=-1;

      }


      if ((b != nbcase-1)&&(M[a][b+1]==color)){

          ajoute_en_tete(&P,a,b+1);
          ajoute_en_tete(L,a,b+1);
          M[a][b+1]=-1;

      }

  }

}



int sequence_aleatoire_imp(int **M, Grille *G, int dim, int nbcl, int aff){
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
        trouve_zone_imp(M, dim, 0, 0, &taille, &L);
        
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
