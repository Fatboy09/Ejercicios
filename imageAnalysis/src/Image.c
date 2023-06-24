#include <stdio.h>
#include <stdlib.h>
#include "../headers/Image.h"

unsigned char* open_bmp(const char* fileName, bmpInfoHeader* infoHeader, bmpFileHeader* fileHeader) {
	
	FILE* stream = fopen(fileName, "rb");
	//bmpFileHeader fileHeader;
	unsigned char* data_image = NULL;
	uint16_t type;
	
	if(stream == NULL) {
		fprintf(stderr, "Error to open bpm image -> %s\n", fileName);
		exit(EXIT_FAILURE);
	}
	
	fread(&type, sizeof(uint16_t), 1, stream);														//leemos los dos primeros bytes
	
	if(type != 0x4D42) {
		fprintf(stderr,"type: %u\nError at image format, must be bmp 24 bits\n", type);
		fclose(stream);
		return NULL;
	}
	
	fread(fileHeader, sizeof(bmpFileHeader),1, stream);												//leemos la cabecera del fichero completa
	
	fread(infoHeader, sizeof(bmpInfoHeader), 1, stream);											// leemos la cabecera de informacion completa
	
	data_image = (unsigned char*) malloc(infoHeader->image_size);									// reservamos espacio en memoria para la imagen ¿cuanta? la que indique imgsize
	
	if(data_image == NULL) {
		fprintf(stderr,"Error at reserve dynamic memory");
		fclose(stream);
		exit(EXIT_FAILURE);
	}
	
	fseek(stream, (long int)fileHeader->offset, SEEK_SET);											// nos situamos en la posicion donde comienza la info de la imagen
	
	fread(data_image, infoHeader->image_size, 1, stream);											// leemos los datos de la imagen, tantos bytes como imgsize
	
	fclose(stream);
	
	return data_image;
}

void save_bmp(const char* fileName, bmpInfoHeader* infoHeader, unsigned char* data_image, bmpFileHeader* fileHeader) {
	
	FILE* stream = fopen(fileName, "wb+");
	uint16_t type;
	
	if(stream == NULL) {
		fprintf(stderr,"Open file failure\n");
        exit(EXIT_FAILURE);
	}
	
  	type = 0x4D42;																					// Escribimos la identificacion del archivo
  	fwrite(&type, sizeof(type), 1, stream);
  	fwrite(fileHeader, sizeof(bmpFileHeader), 1, stream);											// Escribimos la cabecera del archivo
	fwrite(infoHeader, sizeof(bmpInfoHeader), 1, stream);											// Escribimos la informacion basica del archivo
	fwrite(data_image, infoHeader->image_size, 1, stream);											// Escribimos la imagen
	
	fclose(stream);
}

void display_bmpInfoHeader(bmpInfoHeader* infoHeader) {
	
	printf("Header size: %u\n", infoHeader->size_header);
	printf("Width: %d\n", infoHeader->width);
	printf("Height: %d\n", infoHeader->height);
	printf("Color Plane (1): %u\n", infoHeader->color_Plane);
	printf("Bits per Pixel: %u\n", infoHeader->bpp);
	printf("Compression Method: %u\n", infoHeader->compression_Method);
	printf("Image size: %u\n", infoHeader->image_size);
	printf("Horizontal resolution image: %d\n", infoHeader->ppm_x);
	printf("Vertical resolution image %d\n", infoHeader->ppm_y);
	printf("Colors palette: %u\n", infoHeader->colors);
	printf("Number of important colors use: %u\n", infoHeader->imxtcolors);
	
}

void free_bmpImage(unsigned char* image_data) {
	free(image_data);
}
