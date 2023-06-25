#include <stdio.h>
#include <stdlib.h>
#include "../headers/Image.h"
#include "../headers/ImageOperations.h"

int main(int argc, char *argv[]) {
	
	if(argc != 3) {
		fprintf(stderr, "Error, inputs arguments must be 3\n");
		exit(EXIT_FAILURE);
	}
	
	const char* path_file = argv[1];
	const char* path_file_Gray = argv[2];
	bmpInfoHeader infoHeader;
	bmpFileHeader fileHeader;
	unsigned char* image_RGB = open_bmp(path_file, &infoHeader, &fileHeader);
	unsigned char* image_grayScale = NULL;
	
	if(image_RGB != NULL) {
		
		display_bmpInfoHeader(&infoHeader);
		image_grayScale = RGB_to_Gray(image_RGB, infoHeader.width, infoHeader.height);
		save_bmp(path_file_Gray, &infoHeader, image_grayScale, &fileHeader);
		
		free_bmpImage(image_RGB);
		free_bmpImage(image_grayScale);
	}
	
	return 0;
}
