#pragma once
#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdint.h>

#define PNGSIGN_LENGTH 8
#define PNG_PIXELSIZE 4
#define STEG_SIGN_START_LENGTH 10
#define STEG_SIGN_END_LENGTH 8

extern uint8_t _STEG_PAYLOAD_END[];

typedef struct {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
}
pixel_t;


typedef struct
{
	pixel_t *pixels;
	uint32_t width;
	uint32_t height;
}
image_t;

typedef struct
{
	int pixelIndex;
	int channel;
}
injectInfo_t;

typedef void (*pixelCallback_t)(pixel_t *pixel);

//Read and write png files to/from image_t
bool readPNG(const char *filePath, image_t *outImage);
bool writePNG(const char *filePath, image_t *image);

//Process each pixel with callback
void forEachPixel(image_t *image, pixelCallback_t callback);
void cbMakeEven(pixel_t *pixel);

//Steganography stuff
bool containsPayload(image_t *image);
bool injectPayload(image_t *image, uint8_t *payload, long payloadLength);
int extractPayload(image_t *image, uint8_t **destination);

//Read payload file into a buffer
long readPayload(const char *fileName, uint8_t **destination);