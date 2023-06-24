#include <stdio.h>
#include "../headers/Image.h"
#include "../headers/ImageOperations.h"

int main() {
	
	const char* path_file = "./src/resources/tiger.bmp";
	//const char* path_file = "./src/resources/penguin.bmp";
	const char* path_file_Gray = "./src/resources/tiger_gray.bmp";
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
