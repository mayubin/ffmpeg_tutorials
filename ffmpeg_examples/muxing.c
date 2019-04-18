//
// Created by wangrl on 19-4-18.
//

/**
 * Output a media file in any supported libavformat format.
 * The default codecs are used.
 */

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

// a wrapper around a single output AVStream
typedef struct OutputStream {
    AVStream *st;
    AVCodecContext *enc;

    /* pts of the next frame that will be generated */
    int64_t next_pts;
    int samples_count;

    AVFrame *frame;
    AVFrame *tmp_frame;

    float t, tincr, tincr2;

    struct SwsContext *sws_ctx;
    struct SwrContext *swr_ctx;
} OutputStream;

/** Add an output stream. */
static void add_stream(OutputStream *ost, AVFormatContext *oc,
        AVCodec **codec, enum AVCodecID codec_id) {
    AVCodecContext *c;
    int i;

    /* find the encoder */
    *codec = avcodec_find_encoder(codec_id);
    if (!(*codec)) {
        fprintf(stderr, "Could not find encoder for '%s'\n",
                avcodec_get_name(codec_id));
        exit(1);
    }

    ost->st = avformat_new_stream(oc, NULL);
    if (!ost->st) {
        fprintf(stderr, "Could not allocate stream\n");
        exit(1);
    }
    ost->st->id = oc->nb_streams - 1;
    c = avcodec_alloc_context3(*codec);
    if (!c) {
        fprintf(stderr, "Could not alloc an encoding context\n");
        exit(1);
    }
    ost->enc = c;

    switch ((*codec)->type) {

    }
}

int main(int argc, char *argv[]) {

    OutputStream video_st = {0}, audio_st = {0};
    const char *filename;
    AVOutputFormat *fmt;
    AVFormatContext *oc;

    AVCodec *audio_codec, *video_codec;
    int ret;

    int have_video = 0, have_audio = 0;
    int encode_video = 0, encode_audio = 0;

    AVDictionary *opt = NULL;

    int i;

    if (argc < 2) {
        printf("usage: %s output_file\n"
               "API example program to output a media file with libavformat.\n"
               "This program generates a synthetic audio and video stream, encodes and\n"
               "muxes them into a file named output file.\n"
               "The output format is automatically guessed according to the file extension.\n"
               "Raw images can also be output by using '%d%d' in the filename.\n"
               "\n", argv[0]);
        return 1;
    }

    filename = argv[1];
    for (i = 2; i + 1 < argc; i += 2) {
        if (!strcmp(argv[i], "-flags") || !strcmp(argv[i], "-fflags"))
            av_dict_set(&opt, argv[i] + 1, argv[i+1], 0);
    }

    /* allocate the output media context */
    avformat_alloc_output_context2(&oc, NULL, NULL, filename);
    if (!oc) {
        printf("Could not deduce output format from file extension: using MPEG.\n");
        avformat_alloc_output_context2(&oc, NULL, "mpeg", filename);
    }
    if (!oc)
        return 1;

    fmt = oc->oformat;

    /** Add the audio and video streams using the default format codecs
     * and initialize the codecs.
     */
    if (fmt->video_codec != AV_CODEC_ID_NONE) {
        add_stream(&video_st, oc, &video_codec, fmt->video_codec);
        have_video = 1;
        encode_video = 1;
    }


}

