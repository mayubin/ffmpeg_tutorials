//
// Created by wangrl on 19-4-15.
//

/**
 * This is an example of how to use libpng to read and write PNG files.
 */

#include <png.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    int result = 1;

    if (argc == 3) {
        png_image image;

        /* Only the image structure version number needs to be set. */
        memset(&image, 0, sizeof(image));
        image.version = PNG_IMAGE_VERSION;

        if (png_image_begin_read_from_file(&image, argv[1])) {
            png_bytep buffer;

            /**
             * Change this to try different formats! If you set a colormap format
             * then you must also supply a colormap below.
             */
            image.format = PNG_FORMAT_RGBA;
            buffer = malloc(PNG_IMAGE_SIZE(image));

            if (buffer != NULL) {
                if (png_image_finish_read(&image, NULL/*background*/, buffer,
                                          0/*row_stride*/, NULL/*colormap for PNG_FORMAT_FLAG_COLORMAP */)) {
                    if (png_image_write_to_file(&image, argv[2],
                                                0/*convert_to_8bit*/, buffer, 0/*row_stride*/,
                                                NULL/*colormap*/))
                        result = 0;

                    else
                        fprintf(stderr, "png_to_png: write %s: %s\n", argv[2],
                                image.message);

                } else
                    fprintf(stderr, "png_to_png: read %s: %s\n", argv[1],
                            image.message);

                free(buffer);
            } else {
                fprintf(stderr, "png_to_png: out of memory: %lu bytes\n",
                        (unsigned long)PNG_IMAGE_SIZE(image));

                /* This is the only place where a 'free' is required; libpng does
                 * the cleanup on error and success, but in this case we couldn't
                 * complete the read because of running out of memory and so libpng
                 * has not got to the point where it can do cleanup.
                 */
                png_image_free(&image);
            }
        } else {
            /* Failed to read the first argument: */
            fprintf(stderr, "png_to_png: %s: %s\n", argv[1], image.message);
        }
    } else {
        /* Wrong number of arguments */
        fprintf(stderr, "png_to_png: usage: pngtopng input-file output-file\n");
    }

    return result;
}

