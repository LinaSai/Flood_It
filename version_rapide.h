#include<stdio.h>
#include"Liste_case.h"
#include "API_Grille.h"

typedef struct {
    int dim;
    int nbcl;

    ListeCase Lzsg;
    ListeCase* B;
    int** App;
} S_Zsg;

void init_Zsg(int dim,int nbcl,S_Zsg* Zone);

void ajoute_Zsg(int i, int j, S_Zsg* Zone);

void ajoute_Bordure(int i, int j, int cl, S_Zsg* Zone);

int appartient_Zsg(int i, int j, S_Zsg* Zone);

int appartient_Bordure(int i, int j,int cl, S_Zsg* Zone);

int agrandit_Zsg(int** M, S_Zsg* Zone, int color, int i, int j);

int sequence_aleatoire_rapide(int** M, Grille* G,int dim ,int nbcl, int aff);

void detruire_Zsg(S_Zsg* Zone);
