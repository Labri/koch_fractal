/*
 * Fichier : koch_ihm.c
 * Description : Saisie et initialisation des parametres - flocon de koch
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "koch_fonctions.h"
// TODO

void init_parameters(struct parameters *parameters,int argc, char *argv[])
{
	//Initialisation de sparamètre ne fonction des arguments rentrés
	//assert(argv[argc] =  "\0");
	printf("init param");
	parameters->nb_iterations = atoi(argv[3]);
	parameters->segment_length = atoi(argv[1]);
	parameters->image_size = atoi(argv[1]) * 2;
	parameters->fg_color = atoi(argv[4]);
	parameters->bg_color = atoi(argv[5]);
	parameters->all_images = atoi(argv[6]);
	parameters->outfile = argv[7];
	
}

void show_koch_list(struct list *koch)
{
	//Fonction qui affiche la liste sur le terminal
	int i = 0;
	while (koch != NULL){
		printf("[x = %i; y=%i] =>", koch->x, koch->y);
		koch = koch->next;
		i++;
	}
	printf("show koch done, %d\n", i);
}

void show_parameters(const struct parameters *parameters)
{
	//Affichage des parametres 
	printf("shox param : \n");
	printf("segment length => %d\nimage size => %d\nfg_color => %d\nfile =>%s\n", 
	       parameters->segment_length, parameters->image_size ,parameters->fg_color,
	       parameters->outfile);
}
