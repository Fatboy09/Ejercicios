#ifndef IMAGE_HEADER
#define IMAGE_HEADER

#include <stdint.h>

typedef struct BitMapFileHeader {
	uint32_t sizeBMP;					// tamaño del archivo BMP
	uint16_t reserved1;					// reservado
	uint16_t reserved2;					// reservado
	uint32_t offset;					// offset hasta los datos de la imagen
} bmpFileHeader;

typedef struct BitMapInformationHeader {
	uint32_t size_header;				// tamaño del header de información
	int32_t  width;						// width image
	int32_t  height;					// height image
	uint16_t color_Plane;				// planos de color (debe ser 1)
	uint16_t bpp;						// numero de bits por pixel
	uint32_t compression_Method;		// metódo de comprensión
	uint32_t image_size;				// tamaño de la imagen
	int32_t  ppm_x;						// horizontal resolution image
	int32_t  ppm_y;						// vertical resolution image
	uint32_t colors;					// number of colors in the color palette
	uint32_t imxtcolors;				// number of important colors used, 0 if all of them
} bmpInfoHeader;

// Functions
unsigned char* open_bmp(const char* fileName, bmpInfoHeader* infoHeader, bmpFileHeader* fileHeader);
void save_bmp(const char* fileName, bmpInfoHeader* infoHeader, unsigned char* data_image, bmpFileHeader* fileHeader);
void display_bmpInfoHeader(bmpInfoHeader* infoHeader);
void free_bmpImage(unsigned char* image_data);

#endif //IMAGE_HEADER
