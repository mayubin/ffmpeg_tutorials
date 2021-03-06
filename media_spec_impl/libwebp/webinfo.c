//
// Created by wangrl on 19-4-15.
//

#include <stdio.h>
#include <memory.h>
#include "webp/decode.h"
#include "webp/mux_types.h"
#include "imageio/imageio_util.h"


typedef enum {
    WEBP_INFO_OK = 0,
    WEBP_INFO_TRUNCATED_DATA,
    WEBP_INFO_PARSE_ERROR,
    WEBP_INFO_INVALID_PARAM,
    WEBP_INFO_BITSTREAM_ERROR,
    WEBP_INFO_MISSING_DATA,
    WEBP_INFO_INVALID_COMMAND
} WebPInfoStatus;

typedef enum ChunkID {
    CHUNK_VP8,
    CHUNK_VP8L,
    CHUNK_VP8X,
    CHUNK_ALPHA,
    CHUNK_ANIM,
    CHUNK_ANMF,
    CHUNK_ICCP,
    CHUNK_EXIF,
    CHUNK_XMP,
    CHUNK_UNKNOWN,
    CHUNK_TYPES = CHUNK_UNKNOWN
} ChunkID;

typedef struct WebPInfo {
    int canvas_width_;
    int canvas_height_;
    int loop_count_;
    int num_frames_;
    int chunk_counts_[CHUNK_TYPES];
    int anmf_subchunk_counts_[3];  // 0 VP8; 1 VP8L; 2 ALPH.
    uint32_t bgcolor_;
    int feature_flags_;
    int has_alpha_;
    // Used for parsing ANMF chunks.
    int frame_width_, frame_height_;
    size_t anim_frame_data_size_;
    int is_processing_anim_frame_, seen_alpha_subchunk_, seen_image_subchunk_;
    // Print output control.
    int quiet_, show_diagnosis_, show_summary_;
    int parse_bitstream_;
} WebPInfo;

static void WebPInfoInit(WebPInfo * const webp_info) {
    memset(webp_info, 0, sizeof(*webp_info));
}

static int ReadFileToWebPData(const char *const filename,
        WebPData *const webp_data) {
    const uint8_t *data;
    size_t size;

    if (!ImgIoUtilReadFile(filename, &data, &size))
        return 0;
    webp_data->bytes = data;
    webp_data->size = size;

    return 1;
}

static void HelpShort(void) {
    printf("Usage: webpinfo [options] in_files\n"
           "Try -longhelp for an exhaustive list of options.\n");
}

static void HelpLong(void) {
    printf("Usage: webpinfo [options] in_files\n"
           "Note: there could be multiple input files;\n"
           "      options must come before input files.\n"
           "Options:\n"
           "  -version ........... Print version number and exit.\n"
           "  -quiet ............. Do not show chunk parsing information.\n"
           "  -diag .............. Show parsing error diagnosis.\n"
           "  -summary ........... Show chunk stats summary.\n"
           "  -bitstream_info .... Parse bitstream header.\n");
}

// WebP格式分析相关函数
static WebPInfoStatus AnalyzeWebP(WebPInfo *const webp_info,
        const WebPData *webp_data) {

}

int main(int argc, const char *argv[]) {

    int c, quiet = 0, show_diag = 0, show_summary = 0;
    int parse_bitstream = 0;

    WebPInfoStatus webp_info_status = WEBP_INFO_OK;
    WebPInfo webp_info;

    if (argc == 1) {
        HelpShort();
        return WEBP_INFO_OK;
    }

    // Parse command-line input.
    for (c = 1; c < argc; ++c) {
        if (!strcmp(argv[c], "-h") || !strcmp(argv[c], "-help")) {
            HelpShort();
            return WEBP_INFO_OK;
        } else if (!strcmp(argv[c], "-H") || !strcmp(argv[c], "-longhelp")) {
            HelpLong();
        } else if (!strcmp(argv[c], "-quiet")) {
            quiet = 1;
        } else if (!strcmp(argv[c], "-diag")) {
            show_diag = 1;
        } else if (!strcmp(argv[c], "-summary")) {
            show_summary = 1;
        } else if (!strcmp(argv[c], "-bitstream_info")) {
            parse_bitstream = 1;
        } else if (!strcmp(argv[c], "-version")) {
            const int version = WebPGetDecoderVersion();
            printf("WebP Decoder version: %d.%d.%d\n",
                   (version >> 16) & 0xff, (version >> 8) & 0xff, version & 0xff);
            return WEBP_INFO_OK;
        } else {
            // Assume the remaining are all input files.
            break;
        }
    }

    if (c == argc) {
        HelpShort();
        return WEBP_INFO_INVALID_COMMAND;
    }

    // Process input files one by one.
    for (; c < argc; ++c) {
        WebPData webp_data;
        const char *in_file = NULL;
        WebPInfoInit(&webp_info);
        webp_info.quiet_ = quiet;
        webp_info.show_diagnosis_ = show_diag;
        webp_info.show_summary_ = show_summary;
        webp_info.parse_bitstream_ = parse_bitstream;

        in_file = argv[c];
        if (in_file == NULL ||
                !ReadFileToWebPData((const char *)in_file, &webp_data)) {
            webp_info_status = WEBP_INFO_INVALID_COMMAND;
            fprintf(stderr, "Failed to open input file %s.\n", in_file);
            continue;
        }
        if (!webp_info.quiet_)
            printf("File: %s\n", in_file);
        webp_info_status = AnalyzeWebP(&webp_info, &webp_data);
        WebPDataClear(&webp_data);
    }
    return webp_info_status;
}