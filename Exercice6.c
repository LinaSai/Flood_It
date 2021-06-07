#include"Exercice6.h"
#include<stdlib.h>




void initFile(File_Sommet *F){
	F->tete=NULL;
	F->queue=NULL;
}

int File_vide(File_Sommet *F){

	return (F->queue==NULL);
}

int enfiler(File_Sommet *F, Sommet *s){

    Cellule_som2* new= (Cellule_som2*) malloc(sizeof(Cellule_som2));

    if(new == NULL){
        fprintf(stderr,"Erreur d'allocation\n");
        return 0;
    }

    new->sommet=s;
    new->suiv=NULL;

    if(F->tete==NULL){

    	F->tete=new;
    	new->prec=NULL;

    }

    else {
    	F->queue->suiv=new;
   		new->prec=F->queue;
   	}


    F->queue=new;
		F->nb++;
    return 1;

}


Sommet *defiler(File_Sommet *F){

	Sommet* s = NULL;

	if((F->tete) != NULL){

		s = (F->tete)->sommet;
		Cellule_som2* tmp = F->tete;

		if(F->tete == F->queue){
			F->queue=NULL;
			F->tete=tmp->suiv;
		}
		else{
		F->tete=tmp->suiv;
		(F->tete)->prec=NULL;

		}

		free(tmp);
		F->nb--;
	}

	return s;

}




void parcours_largeur( Graphe_zone* Gz,Sommet* s1){

	Cellule_som* Liste_des_sommets = Gz->som;

	while(Liste_des_sommets != NULL){
		(Liste_des_sommets->sommet)->distance = 10000;
		Liste_des_sommets=Liste_des_sommets->suiv;
	}

	File_Sommet File;
  initFile(&File);

	enfiler(&File, s1);
	s1->pere=NULL;
	s1->distance=0;

	Cellule_som* adjacent;
	Sommet* s;

	while (!File_vide(&File)){


		s = defiler(&File);
		adjacent = s->sommet_adj;

		while(adjacent != NULL){


			if ((adjacent->sommet)->distance == 10000){

				enfiler(&File, adjacent->sommet);
				(adjacent->sommet)->pere = s;
				(adjacent->sommet)->distance= s->distance + 1;

			}

			adjacent= adjacent->suiv;

		}

	}


}


Cellule_som* trouver_parcours(Graphe_zone* Gz,Sommet* s1 , Sommet* s2){

    if(s1==s2) return NULL;

	parcours_largeur(Gz,s1);


	Cellule_som* parcours;
	init_cellule(&parcours);

	ajoute_liste_sommet(&parcours, s2);

	Sommet* s = s2->pere;

	while(s!=s1){

		ajoute_liste_sommet(&parcours, s);
		s=s->pere;

	}

	return parcours;


}





int jeu_strategie(int **M,Grille* G, int dim, int nbcl, int aff){


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


   Cellule_som* parcours = trouver_parcours(&Gz,Gz.mat[0][0] ,Gz.mat[Zone.dim-1][Zone.dim-1] );
   Cellule_som* parcours_tmp = parcours;


   while(parcours_tmp != NULL){

   		maj(&Zone, (parcours_tmp->sommet)->cl, aff, G);
		cpt++;
   		parcours_tmp = parcours_tmp->suiv;

   }

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
        maj(&Zone,j,aff,G);
				cpt++;
		// Pour afficher l'etat de la matrice avec l'attribut marque :
        //affichage_jeu(&Gz,Zone.dim);
    }

	detruit_liste_sommet(&parcours);
    detruire_graphe_zone(&Gz, dim );
    detruire_Somme_Zsg(&Zone);

    return cpt;

}
