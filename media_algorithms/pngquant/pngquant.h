//
// Created by wangrl on 19-4-12.
//

#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>

/**
 * PNG read/write functions
 */

typedef enum {
    SUCCESS = 0,
    MISSING_ARGUMENT = 1,
    READ_ERROR = 2,
    INVALID_ARGUMENT = 4,
    NOT_OVERWRITING_ERROR = 15,
    CANT_WRITE_ERROR = 16,
    OUT_OF_MEMORY_ERROR = 17,
    WRONG_ARCHITECTURE = 18,    //  Missing SSE
    PNG_OUT_OF_MEMORY_ERROR = 24,
    LIBPNG_FATAL_ERROR = 25,
    WRONG_INPUT_COLOR_TYPE = 26,
    LIBPNG_INIT_ERROR = 35,
    TOO_LARGE_FILE = 98,
    TOO_LOW_QUALITY = 99
} pngquqant_error;

typedef struct png_rgba {
    unsigned char r, g, b, a;
} png_rgba;

struct png_chunk {
    struct png_chunk *next;
    unsigned char *data;
    size_t size;
    unsigned char name[5];
    unsigned char location;
};

typedef enum {
    PNG_NONE,
    PNG_SRGB,   // sRGB chunk
    PNG_ICCP,   // used ICC profile
    PNG_ICCP_WARN_GRAY,     // ignore and warn about GRAY ICC profile
    PNG_GAMA_CHRM,          // used gAMA and cHRM
    PNG_GAMA_ONLY,          // used gAMA only (i.e. not sRGB)
} png_color_transform;

typedef struct {
    jmp_buf jmpbuf;
    uint32_t width;
    uint32_t height;
    size_t file_size;
    double gamma;
    unsigned char **row_pointers;
    unsigned char *rgba_data;
    struct png_chunk *chunks;

    png_color_transform input_color;
    png_color_transform output_color;
} png24_image;

typedef struct {
    jmp_buf jmpbuf;
    uint32_t width;
    uint32_t height;
    size_t maximum_file_size;
    size_t metadata_size;
    double gamma;
    unsigned char **row_pointers;
    unsigned char *indexed_data;
    struct rwpng_chunk *chunks;
    unsigned int num_palette;
    png_rgba palette[256];
    png_color_transform output_color;
    char fast_compression;
} png8_image;

typedef union {
    jmp_buf jmpbuf;
    png24_image png24;
    png8_image png8;
} png_image;

struct  pngquant_options {

};

/* prototypes for public functions */

void png_version_info(FILE *fp);

pngquqant_error png_read_image24(FILE *infile, png24_image *mainprog_ptr, int strip, int verbose);
pngquqant_error png_write_image8(FILE *outfile, png8_image *mainprog_ptr);
pngquqant_error png_write_image24(FILE *outfile, const png24_image *mainprog_ptr);

void png_free_image24(png24_image *);
void png_free_image8(png8_image *);
