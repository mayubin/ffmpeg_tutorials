//
// Created by wangrl on 19-4-17.
//

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavfilter/buffersink.h>
#include <libavfilter/buffersrc.h>
#include <libavutil/opt.h>
#include <libavutil/pixdesc.h>

/**
 * API example for demuxing, decoding, filtering, encoding and muxing
 */


typedef struct FilteringContext {
    AVFilterContext *buffersink_ctx;
    AVFilterContext *buffersrc_ctx;
    AVFilterGraph *filter_graph;
} FilteringContext;

static int open_input_file(const char *filename) {

}

static int open_output_file(const char *filename) {

}

static int init_filter(FilteringContext *fctx, AVCodecContext *dec_ctx,
        AVCodecContext *enc_ctx, const char *filter_spec) {

}

static void init_filters(void) {

}

int main(int argc, char *argv[]) {

    int ret;
    AVPacket packet = {
            .data = NULL,
            .size = 0
    };
    AVFrame *frame = NULL;
    enum AVMediaType type;
    unsigned int stream_index;
    unsigned int i;

    int got_frame;
    int (*dec_func)(AVCodecContext *, AVFrame *, int *, const AVPacket *);

    if (argc != 3) {
        av_log(NULL, AV_LOG_ERROR, "Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }

    if ((ret = open_input_file(argv[1])) < 0)
        goto end;

    if ((ret = open_output_file(argv[2])) < 0)
        goto end;

    if ((ret = init_filters()) < 0)
        goto end;

    end:
}
