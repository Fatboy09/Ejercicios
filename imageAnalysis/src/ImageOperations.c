#include <stdio.h>
#include <stdlib.h>
#include "../headers/Image.h"

unsigned char* reserve_memory(uint32_t width, uint32_t height) {
	
	unsigned char* array = (unsigned char*) malloc(sizeof(unsigned char) * width * height * 3);
    
    if(array == NULL) {
		fprintf(stderr,"Error at reserve dynamic memory");
		exit(EXIT_FAILURE);
	}
	
    return array;
}

unsigned char* RGB_to_Gray(unsigned char* imageRGB, int32_t width, int32_t height) {
	
	unsigned char* imageGray = reserve_memory((uint32_t)width, (uint32_t)height);
	unsigned char scaleGray;
	
	for(register int y = 0; y < height; y++) {
		for(register int x = 0; x < width; x++) {
			int index_Gray = (y * width + x) * 3;
			int index_RGB  = index_Gray;
			
			scaleGray = (unsigned char)(((imageRGB[index_RGB]) * 0.11) + ((imageRGB[index_RGB + 1]) * 0.59) + ((imageRGB[index_RGB + 2]) * 0.3));
			
			imageGray[index_Gray]     = scaleGray;
			imageGray[index_Gray + 1] = scaleGray;
			imageGray[index_Gray + 2] = scaleGray; 
		}
	}

    return imageGray;
}
