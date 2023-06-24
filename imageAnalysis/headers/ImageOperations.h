#ifndef IMAGEOPERATIONS_HEADER
#define IMAGEOPERATIONS_HEADER

#include <stdint.h>

unsigned char* RGB_to_Gray(unsigned char* imageRGB, int32_t width, int32_t height);
unsigned char* reserve_memory(uint32_t width, uint32_t height);

#endif // IMAGEOPERATIONS_HEADER
