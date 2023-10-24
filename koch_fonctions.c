/*
 * Fichier : koch_fonctions.c
 * Description : Trace de fractales geometriques - flocon de koch - generation des points et rendu des lignes
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "koch_fonctions.h"
#include "create_image.h"
#include <math.h>
#include <assert.h>

#define M_PI 3.14159265358979323846

// TODO

/* Initialisation de la liste chainee koch correspondant au triangle
   de Koch initial */
void init_koch(struct list **koch, uint32_t size, uint32_t segment_length)
{
	assert(size >= segment_length);
	int moit = segment_length / 2;
	struct list *PC = malloc(sizeof(struct list)); 
	PC->x = segment_length + moit / 2;
	PC->y = moit;
	PC->next = NULL;
	struct list *PB = malloc(sizeof(struct list));
	PB->x = 3 * moit / 2;
	PB->y = moit + sqrt((segment_length*segment_length) - (moit * moit ));
	PB->next = PC;
	struct list *PA = malloc(sizeof(struct list));
	PA->x = moit / 2;
	PA->y = moit;
	PA->next = PB;
	*koch = PA;
	printf("init koch done\n");
}

/* Initialisation de l'image avec la couleur de fond definie dans les
   parametres */
void init_picture(uint32_t **picture, uint32_t size, uint32_t bg_color)
{
	uint32_t pic[size * size - 1];
	for(uint32_t i = 0; i < size * size; i++){
		pic[i] = bg_color;}
	*picture = pic;
	printf("Init picture done\n");
	/*on fait un tableau size*size, chaque case contient la couleur de bg a la base.
	  ensuite on modifiera les cases interesesantes en changeant leur couleur*/
        
}

/* Calcul de la fractale de Koch apres un nombre d'iterations donne ;
   generation de la liste chainee koch correspondante */
void generer_koch(struct list *koch, uint32_t nb_iterations)
{
	
	for(uint32_t i = 0; i < nb_iterations; i++){
		struct list *sent = koch;
		struct list *ptA = sent;
		struct list *ptE = sent->next;
		while(ptE != NULL){
			struct list *PB = malloc(sizeof(struct list));
			struct list *PC = malloc(sizeof(struct list));
			struct list *PD = malloc(sizeof(struct list));
			/*printf("boucle\n");*/
			PB->x = ptA->x + (ptE->x - ptA->x) / 3;
			PB->y = ptA->y + (ptE->y - ptA->y) / 3;
			PB->next = PC;
			PD->x = ptA->x + 2 * (ptE->x - ptA->x) / 3;
			PD->y = ptA->y + 2 * (ptE->y - ptA->y) / 3;
			PD->next = ptE;
			PC->x = (PB->x + PD->x) * cos(M_PI / 3) - (PD->y - PB->y) * sin(M_PI / 3);
			PC->y = (PB->y + PD->y) * cos(M_PI / 3) + (PD->x - PB->x) * sin(M_PI / 3);
			PC->next = PD;
			ptA->next = PB;
			ptA = ptE;
			ptE = ptE->next;}

/* on fait une derniere etape pour le dernier segment qui revient sur la point de départ.*/
     
		struct list *PB = malloc(sizeof(struct list));
                struct list *PC = malloc(sizeof(struct list));
                struct list *PD = malloc(sizeof(struct list));
		/*printf("last segment\n");*/
		ptE = koch;
		PB->x = ptA->x + ptE->x /3 - ptA->x / 3;
		PB->y = ptA->y + ptE->y / 3 - ptA->y / 3;
		PB->next = PC;
		PD->x = ptA->x + (2 * ptE->x / 3) - (2 * ptA->x / 3);
		PD->y = ptA->y + 2 * (ptE->y / 3) - (2 * ptA->y) / 3;
		PD->next = NULL;
		PC->x = (PB->x + PD->x) * cos((M_PI / 3)) - (PD->y - PB->y) * sin((M_PI / 3));
		PC->y = (PB->y + PD->y) * cos((M_PI / 3)) + (PD->x - PB->x) * sin((M_PI / 3)) ;
		PC->next = PD;
		ptA->next = PB;
		koch = sent;
	}
	printf("generer koch done \n");
	
}

/* Rendu image via algorithme bresehem - version generalisee
   simplifiee */
void render_image_bresenham(uint32_t *picture, struct list *koch, uint32_t size, uint32_t fg_color)
{
	printf("Start Bresenh\n");
	struct list *prec = koch;
	struct list *cour = prec->next;
	int32_t dx;
	int32_t dy;
	int8_t sx;
	int8_t sy;
	int x0, x1;
	int y0, y1;
	
	while(cour != NULL){
		x0 = prec->x;
		y0 = prec->y;
		x1 = cour->x;
		y1 = cour->y;
		dx = abs(x1 - x0);
		dy = abs(y1 - y0);
		sx = (x0 < x1) ? 1 : -1;
		sy = (y0 < y1) ? 1 : -1;


		int32_t err = dx - dy;
		while(x0 != x1 || y0 != y1){
		int32_t e2;
			picture[x0 * size + y0] = fg_color;
			e2 = 2 * err;
			if (e2 > -dy){
				err -= dy;
				x0 += sx;
			}
			if(e2 < dx){
				err += dx;
				y0 += sy;
			}

			
		}
		prec = cour;
		cour = cour->next;
		
		
	}
	/* On n'oulbie pas le dernier segment, celui qui a pour arrivé Koch*/
	cour = koch;
	x0 = prec->x;
	y0 = prec->y;
	x1 = cour->x;
	y1 = cour->y;
	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;


	
	int32_t err = dx - dy;
	while(x0 != x1 || y0 != y1){
	int32_t e2;
		picture[x0 * size + y0] = fg_color;
		e2 = 2 * err;
		if (e2 > -dy){
			err -= dy;
			x0 += sx;
		}
		if(e2 < dx){
			err += dx;
			y0 += sy;
		}

	}
	printf("end Bresen\n");
}


/* Liberation de la memoire allouee a la liste chainee */
void free_koch(struct list *koch)
{
	while (koch != NULL){
		free(koch);
		koch = koch->next;
	}
	printf("free done\n");
}
