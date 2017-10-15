/*
 * Fichier : create_image.c
 * Description : Creation d'un fichier ppm a partir d'une image sous la forme
 *               d'un tableau uint32_t *
 */
#include "create_image.h"
#include <stdlib.h>
#include <stdio.h>
// TODO

void create_image_ppm(uint32_t *picture, int32_t size_x, int32_t size_y, char *file_name)
{
	FILE *f = fopen(file_name, "w");
	fprintf(f, "P6\n");
	fprintf(f, "%d %d\n", size_x, size_y);
	fprintf(f, "255\n");
	fclose(f);
	f = fopen(file_name, "ab+");
	for(int i = 0; i < size_x * size_y ; i++){
		//printf("%i\n", picture[i]) ;
		int k = picture[i] & 0x000000FF;
		fwrite(&k,1,1,f);
		k = (picture[i] >> 8) & 0x000000FF;
		fwrite(&k,1,1,f);
		k =(picture[i] >> 16) & 0x000000FF;
		fwrite(&k,1,1,f);
	}
	fclose(f);

}

