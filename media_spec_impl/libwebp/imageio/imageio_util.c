//
// Created by wangrl on 19-4-16.
//

#include <memory.h>
#include <malloc.h>
#include "imageio_util.h"

int ImgIoUtilReadFromStdin(const uint8_t** data, size_t* data_size) {

    return 0;
}

int ImgIoUtilReadFile(const char *const file_name, const uint8_t **data, size_t *data_size) {
    int ok;
    uint8_t *file_data;
    size_t file_size;
    FILE *in;

    const int from_stdin = (file_name == NULL) || !strcmp(file_name, "-");

    if (from_stdin) return ImgIoUtilReadFromStdin(data, data_size);

    if (data == NULL || data_size == NULL)
        return 0;

    *data = NULL;
    *data_size = 0;

    in = fopen(file_name, "rb");
    if (in == NULL) {
        fprintf(stderr, "cannot open input file '%s'\n", file_name);
        return 0;
    }

    fseek(in, 0, SEEK_END);
    file_size = ftell(in);
    fseek(in, 0, SEEK_SET);

    // we allocate one extra byte for the \0 terminator
    file_data = (uint8_t *)malloc(file_size + 1);
    if (file_data == NULL) {
        fclose(in);
        fprintf(stderr, "memory allocation failure when reading file %s\n", file_name);
        return 0;
    }

    ok = (fread(file_data, file_size, 1, in) == 1);
    fclose(in);

    if (!ok) {
        fprintf(stderr, "Could not read %d bytes of data from file %s\n",
                (int)file_size, file_name);
        return 0;
    }

    file_data[file_size] = '\0';        // convenient 0-terminator
    // 通过双重指针改变指针指向的地址。
    *data = file_data;
    *data_size = file_size;
    return 1;
}


