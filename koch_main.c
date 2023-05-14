/*
 * Fichier : koch_main.c
 * Description : Trace de fractales geometriques - flocon de koch - programme principal
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include "koch_fonctions.h"
#include "koch_ihm.h"
#include "create_image.h"

int main(int argc, char **argv)
{
	struct list *koch;
	struct parameters param;
	uint32_t *picture;
	if(argc <= 7){
		printf("For good use :\n");
		printf("./koch 'seg_length' 'img_size' 'nb_it' 'fg_color' 'bg_color 'string' bpm_file\n");
		printf("for the fiels 'string' enter 'all' if you want the program to generate an image for each iteration\n");
		return EXIT_FAILURE;}

	printf("start\n");
	init_parameters(&param, argc, argv);
	show_parameters(&param);
	init_koch(&koch, param.image_size, param.segment_length);
        if(strcmp(argv[6], "all") == 0 && param.nb_iterations > 0){  // XXXX
		/* Si l'utilisateur a rentré en argument 'all' 
		   alors on affiche chaque image pour chaque itération*/
		char *name[param.nb_iterations];
		for(int i = 1; i <= param.nb_iterations; i++){
			sprintf(*name, "%i_koch.ppm", i);
			printf("génération de la %dieme image %s \n", i, *name);
			generer_koch(koch, 1);
			init_picture(&picture, param.image_size, param.segment_length);
			render_image_bresenham(picture, koch, param.image_size, param.fg_color);
			create_image_ppm(picture, param.image_size, param.image_size, name[i]); //problème lors de l'appel de la fonction.
		}
	}
	else{
		init_picture(&picture, param.image_size, param.segment_length);
		if (param.nb_iterations > 0){
			generer_koch(koch, param.nb_iterations);
		}
		show_koch_list(koch);
		render_image_bresenham(picture, koch, param.image_size, param.fg_color);
	    create_image_ppm(picture, param.image_size, param.image_size, param.outfile);
	}
	free_koch(koch);
	return EXIT_SUCCESS;

}
