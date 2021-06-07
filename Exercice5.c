#include"Exercice5.h"
#include<stdio.h>
#include<stdlib.h>


void init_Somme_Zsg(int dim,int nbcl,Somme_Zsg* Zone){
    Zone -> dim = dim;
    Zone -> nbcl = nbcl;
    Zone->Lzsg = NULL;

    Zone -> B = (Cellule_som **)malloc(nbcl * sizeof(Cellule_som *));

    int j;
    for(j=0;j<nbcl;j++){
        init_cellule((Zone->B)+j);
    }

    Zone -> tab_taille = (int *)malloc(nbcl * sizeof(int));
    for(j=0;j<nbcl;j++){
        Zone->tab_taille[j]=0;
    }
}


void ajoute_Somme_Zsg(Sommet* s, Somme_Zsg* Zone){
    ajoute_liste_sommet(&(Zone->Lzsg), s);
    s->marque=0;
}

void ajoute_Somme_Bordure(Sommet* s, Somme_Zsg* Zone){
    int i=s->cl;
    ajoute_liste_sommet((Zone->B)+i , s);
    s->marque=1;

    Zone->tab_taille[s->cl] += s->nbcase_som;
}



int appartient_Somme_Zsg(Sommet* s, Somme_Zsg* Zone){
    return (s->marque==0);
}


int appartient_Somme_Bordure(Sommet* s, Somme_Zsg* Zone){
    return (s->marque==1);
}

void afficher_sommet ( Sommet* s){

    if(s!=NULL){
        printf("sommet de couleur : %d , numero %d \n",s->cl,s->num);

    }
}
void afficher_liste_sommet(Somme_Zsg* Zone, int color){

    Cellule_som* tmp1= (Zone)->B[color];

    if (tmp1==NULL)
        printf("Liste vide \n");

    else{
        while(tmp1!=NULL){
            afficher_sommet(tmp1->sommet);
            tmp1=(tmp1)->suiv;

        }
    }
}

void afficher_Lzsg(Somme_Zsg* Zone){
    Cellule_som* tmp = Zone->Lzsg;
    if(est_vide(&Zone->Lzsg))
        printf("Lzsg Vide\n");

    while(tmp){
        printf("appartient a Lzsg : "); afficher_sommet(tmp->sommet);
        tmp=tmp->suiv;
    }
}


void affichage_jeu(Graphe_zone* Gz, int dim){
    int i,j;

    for(i=0; i<dim; i++){
        for(j=0; j<dim; j++){
            Sommet* tmp = Gz->mat[j][i];

            printf("%d\t",tmp->marque);

        }
        printf("\n");
    }
}


void maj(Somme_Zsg* Zone,int color,int aff,Grille *G){

	 Cellule_som* Lzsg = Zone->Lzsg;
	 ListeCase liste;

		if(aff==1){
			Lzsg = Zone->Lzsg;

			while(Lzsg != NULL){

	 			liste = (Lzsg->sommet)->cases;

	 			while(liste != NULL){
					Grille_attribue_couleur_case(G, liste->i, liste->j ,color);
					liste=liste->suiv;
				}

			Lzsg=Lzsg->suiv;
		}

			Grille_attente_touche();
			Grille_redessine_Grille(G);
		}

    Cellule_som* tmp = Zone->B[color];

    while(tmp){

        if (!appartient_Somme_Zsg((tmp)->sommet, Zone)){

            ajoute_Somme_Zsg((tmp)->sommet, Zone);


            //mise a jour de la bordure de la Zsg
            Cellule_som* liste_adj = ((tmp)->sommet)->sommet_adj;

            while(liste_adj != NULL){

                if (!appartient_Somme_Bordure(liste_adj->sommet, Zone) && !appartient_Somme_Zsg(liste_adj->sommet, Zone)){
                    ajoute_Somme_Bordure(liste_adj->sommet, Zone);
                }

                liste_adj=liste_adj->suiv;
            }
        }

        tmp=(tmp)->suiv;
    }

    Zone->tab_taille[color]=0;
    detruit_liste_sommet(Zone->B+color);

}


int bordure_vide(Somme_Zsg* Zone){
    int i;
    for(i=0;i<Zone->nbcl;i++){
        if (!est_vide(Zone->B+i ))
            return 0;
    }

    return 1;
}




int max_bordure( int** M, Grille* G,int dim, int nbcl, int aff ){

   Graphe_zone Gz;
   creer_graphe_zone(&Gz, dim,  M);

   Somme_Zsg Zone;
   init_Somme_Zsg( dim, nbcl, &Zone);

   int cpt=0;
    ajoute_Somme_Zsg(Gz.mat[0][0],&Zone);

    Cellule_som* sommet_adj = (Gz.mat[0][0])->sommet_adj;

    while(sommet_adj != NULL){

        if (!appartient_Somme_Bordure(sommet_adj->sommet, &Zone))
            ajoute_Somme_Bordure(sommet_adj->sommet, &Zone);

        sommet_adj=sommet_adj->suiv;
    }

    //affichage texte avec la fonction affichage jeu :

   // affichage_jeu(&Gz,Zone.dim);
     //printf("\n\n\n");

    int max,i;

    while(!bordure_vide(&Zone)){

        max=Zone.tab_taille[0];
        int j=0;

        for(i=1;i<Zone.nbcl;i++){
            if (Zone.tab_taille[i] > max){
            	j=i;
                max=Zone.tab_taille[i];
            }
        }

        maj( &Zone,j,aff,G);
        cpt++;
       // affichage_jeu(&Gz,Zone.dim);
       // printf("\n\n\n");

    }
    detruire_graphe_zone(&Gz, Zone.dim );
    detruire_Somme_Zsg(&Zone);
    return cpt;
}


void detruire_Somme_Zsg(Somme_Zsg* Zone){
//Dans cette fonction on a fait l hypothese qu on l appellerait apres libere graphe zone qui liberera les sommets
    detruit_liste_sommet(&(Zone->Lzsg));
     free(Zone->tab_taille);
     free(Zone->B); // ici aussi la bordure est vide car on l appelle apres max_bordure

}
