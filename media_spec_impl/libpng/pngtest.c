//
// Created by wangrl on 19-4-12.
//

#include <png.h>
#include <zlib.h>
#include <memory.h>
#include <stdlib.h>

static int verbose = 0;
static int strict = 0;
static int relaxed = 0;
static int xfail = 0;
static int unsupported_chunks = 0;  /* chunk unsupported by libpng in input */
static int error_count = 0;     /* count calls to png_error */
static int warning_count = 0;   /* count calls to png_warning */

/* Example of using row callbacks to make a simple progress meter */
static int status_pass = 1;
static int status_dots_requested = 0;
static int status_dots = 1;

static const char *inname = "pngtest.png";
static const char *outname = "pngout.png";

int main(int argc, char *argv[]) {

    // multiple files
    // 增加-m 表示输入多个文件。
    int multiple = 0;
    int ierror = 0;

    png_structp  dummy_ptr;

    fprintf(stderr, "\n Testing libpng version %s\n", PNG_LIBPNG_VER_STRING);
    fprintf(stderr, " with zlib version %s\n", ZLIB_VERSION);

    /* Show the version of libpng used in building the library */
    fprintf(stderr, " library (%lu):%s",
            (unsigned long) png_access_version_number(), png_get_header_version(NULL));

    if (strcmp(png_libpng_ver, PNG_LIBPNG_VER_STRING)) {
        fprintf(stderr, "Warning: versions are different between png.h and png.c\n");
        fprintf(stderr, " png.h version: %s\n", PNG_LIBPNG_VER_STRING);
        fprintf(stderr, " png.c version: %s\n\n", png_libpng_ver);
        ++ierror;
    }

    if (argc > 1) {
        if (strcmp(argv[1], "-m") == 0) {
            multiple = 1;
            status_dots_requested = 0;
        } else if (strcmp(argv[1], "-mv") == 0 || strcmp(argv[1], "-vm") == 0) {
            multiple = 1;
            verbose = 1;
            status_dots_requested = 1;
        } else if (strcmp(argv[1], "-v") == 0) {
            verbose = 1;
            status_dots_requested = 1;
            inname = argv[2];
        } else if (strcmp(argv[1], "--strict") == 0) {
            status_dots_requested = 0;
            verbose = 1;
            inname = argv[2];
            strict++;
            relaxed = 0;
            multiple = 1;
        } else if (strcmp(argv[1], "--relaxed") == 0) {
            status_dots_requested = 0;
            verbose = 1;
            inname = argv[2];
            strict = 0;
            relaxed++;
            multiple=1;
        } else if (strcmp(argv[1], "--xfail") == 0) {
            status_dots_requested = 0;
            verbose = 1;
            inname = argv[2];
            strict = 0;
            xfail++;
            relaxed++;
            multiple=1;
        } else {
            inname = argv[1];
            status_dots_requested = 0;
        }
    }

    if (multiple == 0 && argc == 3 + verbose)
        outname = argv[2 + verbose];

    if ((multiple == 0 && argc > 3 + verbose) ||
            (multiple != 0 && argc < 2)) {
        fprintf(stderr, "usage: %s [infile.png] [outfile.png]\n\t%s -m {infile.png}\n",
                argv[0], argv[0]);
        fprintf(stderr, " reads/writes one PNG file (without -m) or multiple files (-m)\n");
        fprintf(stderr, " with -m %s is used as a temporary file\n", outname);
        exit(1);
    }
}

