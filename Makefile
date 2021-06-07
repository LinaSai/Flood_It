LFLAGS=-lSDL2 -lSDL2_image

all: Flood-It_Partie1

API_Gene_instance.o: API_Gene_instance.c API_Gene_instance.h
	gcc -c API_Gene_instance.c `sdl2-config --cflags`

API_Grille.o: API_Grille.c API_Grille.h
	gcc -c API_Grille.c `sdl2-config --cflags`

Liste_case.o: Liste_case.c Liste_case.h
	gcc -c Liste_case.c `sdl2-config --cflags`

Fonctions_exo1.o: Fonctions_exo1.c Entete_Fonctions.h Liste_case.h
	gcc -g -c Fonctions_exo1.c `sdl2-config --cflags`

exercice2.o: exercice2.c exercice2.h Liste_case.h
	gcc -g -c exercice2.c `sdl2-config --cflags`

version_rapide.o: version_rapide.c version_rapide.h Liste_case.h
	gcc -g -c version_rapide.c `sdl2-config --cflags`

Exercice4.o: Exercice4.c Exercice4.h Liste_case.h exercice2.h
	gcc -g -c Exercice4.c `sdl2-config --cflags`

Exercice5.o: Exercice5.c Exercice5.h Exercice4.h
	gcc -g -c Exercice5.c `sdl2-config --cflags`

Exercice6.o: Exercice6.c Exercice6.h Exercice4.h
	gcc -g -c Exercice6.c `sdl2-config --cflags`

Flood-It_Partie1.o: Flood-It_Partie1.c
	gcc -g -c Flood-It_Partie1.c `sdl2-config --cflags`

Flood-It_Partie1: Flood-It_Partie1.o Liste_case.o  API_Grille.o API_Gene_instance.o Fonctions_exo1.o exercice2.o version_rapide.o Exercice4.o Exercice5.o Exercice6.o
	gcc -g -o Flood-It_Partie1 Flood-It_Partie1.o Liste_case.o API_Grille.o API_Gene_instance.o Fonctions_exo1.o exercice2.o version_rapide.o Exercice4.o Exercice5.o Exercice6.o `sdl2-config --libs`

clean:
	rm -f *.o Flood-It_Partie1
