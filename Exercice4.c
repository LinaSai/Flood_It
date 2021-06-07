#include"Exercice4.h"
#include"Entete_Fonctions.h"
#include<stdio.h>
#include<stdlib.h>


void init_cellule(Cellule_som** L){
  *(L)=NULL;
}

int est_vide(Cellule_som** L){
  return (*L)==NULL;
}

int ajoute_liste_sommet(Cellule_som** L, Sommet* S){

    Cellule_som* nouveau= (Cellule_som*) malloc(sizeof(Cellule_som));
    if(nouveau == NULL){
        fprintf(stderr,"Erreur d'allocation\n");
        return 0;
    }
    nouveau->sommet=S;
    nouveau->suiv=*L;
    (*L)=nouveau;
    return 1;
}



void detruit_liste_sommet(Cellule_som** L){
     Cellule_som *cour,*prec;
      cour=(*L);
      while (cour!=NULL){
        prec=cour;
        cour=cour->suiv;
        free(prec);
      }

      *L=NULL;
}


void ajoute_voisin(Sommet* s1, Sommet* s2){

    ajoute_liste_sommet(&(s1->sommet_adj),s2);
    ajoute_liste_sommet(&(s2->sommet_adj),s1);

}

int adjacents(Sommet* s1, Sommet* s2){

    Cellule_som* Liste = s1->sommet_adj;

    while (Liste!=NULL){

      if(Liste->sommet==s2)
          return 1;
      Liste=Liste->suiv;

    }

    return 0;
}





void creer_graphe_zone(Graphe_zone* Gz, int dim, int** M){

    Gz->nbsom=0;
    Gz->som=NULL;
    Gz->mat=(Sommet***) malloc(dim*sizeof(Sommet**));

    int i,j;
    for( i=0; i<dim; i++){
        Gz->mat[i]= (Sommet**) malloc (dim * sizeof(Sommet*));
        for( j=0; j<dim; j++){
            Gz->mat[i][j]=NULL;
        }

    }

    int cpt=0;
    for( i=0; i<dim; i++){
        for( j=0; j<dim; j++){

            if(Gz->mat[i][j]==NULL){


                Gz->mat[i][j]=(Sommet*) malloc(sizeof(Sommet));
                (Gz->mat[i][j])->num=cpt;
                (Gz->mat[i][j])->cl=M[i][j];
                (Gz->mat[i][j])->sommet_adj=NULL;
                (Gz->mat[i][j])->marque=2; // demande a l exercice 5

                (Gz->mat[i][j])->distance=5000000;
                (Gz->mat[i][j])->pere=NULL;

                int a=0;
                ListeCase L;
                init_liste(&L);

                trouve_zone_rec(M,dim,i,j,&a,&L);

                (Gz->mat[i][j])->nbcase_som=a;

                init_liste(&(Gz->mat[i][j]->cases));


                 ListeCase tmp=L;

                 while(tmp){
                   Gz->mat[tmp->i][tmp->j]=Gz->mat[i][j];
                    ajoute_en_tete(&(Gz->mat[i][j]->cases), tmp->i, tmp->j);
                    tmp=tmp->suiv;
                 }


                 ajoute_liste_sommet(&(Gz->som),Gz->mat[i][j]);
                 Gz->nbsom++;
                 detruit_liste(&L);
                cpt++;
           }

        }
    }




    for(i=0; i<dim; i++){
        for(j=0; j<dim; j++){


                if (i != 0 && Gz->mat[i-1][j]!= Gz->mat[i][j]){
                    if (! adjacents(Gz->mat[i-1][j] , Gz->mat[i][j]))
                        ajoute_voisin(Gz->mat[i-1][j], Gz->mat[i][j]);

                }

                if (i != dim-1 && Gz->mat[i+1][j]!=Gz->mat[i][j]){
                    if (! adjacents(Gz->mat[i+1][j] , Gz->mat[i][j]))
                        ajoute_voisin(Gz->mat[i+1][j], Gz->mat[i][j]);
                }

                if (j != 0 && Gz->mat[i][j-1] != Gz->mat[i][j]){
                    if (! adjacents(Gz->mat[i][j-1] , Gz->mat[i][j]))
                        ajoute_voisin(Gz->mat[i][j-1], Gz->mat[i][j]);

                }

                if (j != dim-1 && Gz->mat[i][j+1] != Gz->mat[i][j]){
                    if (! adjacents(Gz->mat[i][j+1] , Gz->mat[i][j]))
                        ajoute_voisin(Gz->mat[i][j+1], Gz->mat[i][j]);
                }
        }
    }


}

void affichage(Graphe_zone* Gz, int dim){

  printf("\n Affichage de la matrice des numeros \n");
    int i,j;

    for(i=0; i<dim; i++){
        for(j=0; j<dim; j++){
            Sommet* tmp = Gz->mat[j][i];

            printf("%d\t",tmp->num);

        }
        printf("\n");
    }


    printf("Affichage des sommets adjacents\n");

    Cellule_som* tmp1=Gz->som;

    while(tmp1 != NULL){

        Sommet* tmp2 =  tmp1->sommet;
        Cellule_som* tmp3 = tmp2->sommet_adj;

        printf("sommet %d, ses adjacents sont : ",tmp2->num);

        while(tmp3 != NULL){
            Sommet* tmp4 =  tmp3->sommet;
            printf("%d  ",tmp4->num);

            tmp3=tmp3->suiv;
        }
        printf("\n");


        tmp1=tmp1->suiv;
    }

}

void detruire_sommet(Sommet* s){
  detruit_liste(&(s->cases));
  detruit_liste_sommet(&(s->sommet_adj));
  free(s);

}

void detruire_graphe_zone(Graphe_zone* Gz, int dim ){

    //Destruction de la liste des sommets

    Cellule_som *cour,*prec;
     cour=Gz->som;
     while (cour!=NULL){
       prec=cour;
       cour=cour->suiv;
      detruire_sommet(prec->sommet);
      free(prec);

     }


      //Destruction de la matrice
      int i;

      for(i=0; i<dim; i++)
          free(Gz->mat[i]);

      free(Gz->mat);

}
