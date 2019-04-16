//
// Created by wangrl on 19-4-16.
//

// Utility functions used by the image decoders.

#pragma once

#include <stdio.h>
#include "webp/types.h"

#ifdef __cplusplus
extern "C" {
#endif

// File I/O

// Reopen file in binary (O_BINARY) mode.
// Returns 'file' on success, NULL otherwise.
FILE *ImgIoUtilSetBinaryMode(FILE *file);

// Allocates storage for entire file 'file_name' and returns contents and size
// in 'data' and 'data_size'. Returns 1 on success, 0 otherwise. '*data' should
// be deleted using free().
// Note: for convenience, the data will be null-terminated with an extra byte
// (not accounted for in *data_size), in case the file is text and intended
// to be used as a C-string.
// If 'file_name' is NULL or equal to "-", input is read from stdin by calling
// the function ImgIoUtilReadFromStdin().
int ImgIoUtilReadFile(const char * const file_name,
        const uint8_t **data, size_t *data_size);

// Same as ImgIoUtilReadFile(), but reads until EOF from stdin instead.
int ImgIoUtilReadFromStdin(const uint8_t **data, size_t *data_size);

// Write a data segment into a file named 'file_name'. Returns true if ok.
// If 'file_name' is NULL or equal to "-", output is written to stdout.
int ImgIoUtilWriteFile(const char * const file_name,
        const uint8_t *data, size_t data_size);

// Copy width x height pixels from 'src' to 'dst honoring the strides.
void ImgIoUtilCopyPlane(const uint8_t *src, int src_stride,
        uint8_t *dst, int dst_stride, int width, int height);

// Returns 0 in case of overflow of nmemb * size.
int ImgToUtilCheckSizeArgumentsOverflow(uint64_t nmemb, size_t size);



#ifdef __cplusplus
};      // extern "C"
#endif

