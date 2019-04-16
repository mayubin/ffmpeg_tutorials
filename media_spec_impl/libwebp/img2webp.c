//
// Created by wangrl on 19-4-16.
//

/**
 * generate an animated WebP out of a sequence of images (PNG, JPEG, ...)
 *
 * Example usage:
 *      img2webp -o out.webp -q 40 -mixed -duration 40 input??.png
 */

#include <stdio.h>
#include "webp/encode.h"
#include "webp/decode.h"


static void Help(void) {
    printf("Usage:\n\n");
    printf("  img2webp [file-level options] [image files...] "
           "[per-frame options...]\n");
    printf("\n");

    printf("File-level options (only used at the start of compression):\n");
    printf(" -min_size ............ minimize size\n");
    printf(" -loop <int> .......... loop count (default: 0, = infinite loop)\n");
    printf(" -kmax <int> .......... maximum number of frame between key-frames\n"
           "                        (0=only keyframes)\n");
    printf(" -kmin <int> .......... minimum number of frame between key-frames\n"
           "                        (0=disable key-frames altogether)\n");
    printf(" -mixed ............... use mixed lossy/lossless automatic mode\n");
    printf(" -v ................... verbose mode\n");
    printf(" -h ................... this help\n");
    printf(" -version ............. print version number and exit\n");
    printf("\n");

    printf("Per-frame options (only used for subsequent images input):\n");
    // 表示animation webp的帧率，如果d == 40, 表示每秒钟需要25张图片。
    printf(" -d <int> ............. frame duration in ms (default: 100)\n");
    printf(" -lossless  ........... use lossless mode (default)\n");
    printf(" -lossy ... ........... use lossy mode\n");
    printf(" -q <float> ........... quality\n");
    printf(" -m <int> ............. method to use\n");

    printf("\n");
    printf("example: img2webp -loop 2 in0.png -lossy in1.jpg\n"
           "                  -d 80 in2.tiff -o out.webp\n");
    printf("\nNote: if a single file name is passed as the argument, the "
           "arguments will be\n");
    printf("tokenized from this file. The file name must not start with "
           "the character '-'.\n");
}


int main(int argc, char *argv[]) {

    const char *output = NULL;
    WebPAnimEncoder * enc = NULL;

    return 0;
}

