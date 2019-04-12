//
// Created by wangrl on 19-4-10.
//

#include <libavformat/avformat.h>

static void save_gray_frame(unsigned char *buf, int wrap, int xsize, int ysize, char *filename) {
    FILE *f = fopen(filename, "w");

    // writing the minimal required header for a pgm file format.
    fprintf(f, "P5\n%d %d\n%d\n", xsize, ysize, 255);

    // writing line by line
    for (int i = 0; i < ysize; i++) {
        fwrite(buf + i * wrap, 1, xsize, f);
    }
    fclose(f);
}

static int decode_packet(AVPacket *pPacket, AVCodecContext *pCodecContext, AVFrame *pFrame) {
    // Supply raw packet data as input to a decoder
    int response = avcodec_send_packet(pCodecContext, pPacket);

    while (response >= 0) {

        // Return decoded output data (into a frame) from a decoder
        response = avcodec_receive_frame(pCodecContext, pFrame);

        if (response == AVERROR(EAGAIN) || response == AVERROR_EOF) {
            break;
        }

        if (response >= 0) {
            printf("Frame %d (type = %c, size = %d bytes) pts %ld key_frame %d [DTS %d]\n",
                   pCodecContext->frame_number,
                   av_get_picture_type_char(pFrame->pict_type),
                   pFrame->pkt_size,
                   pFrame->pts,
                   pFrame->key_frame,
                   pFrame->coded_picture_number);

            char frame_filename[1024];
            snprintf(frame_filename, sizeof(frame_filename), "%s-%d.pgm", "frame", pCodecContext->frame_number);

            // Save a gray scale frame into a .pgm file
            save_gray_frame(pFrame->data[0], pFrame->linesize[0], pFrame->width, pFrame->height, frame_filename);

            av_frame_unref(pFrame);
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {

    // AVFormatContext holds the header information from the format (Container)
    // Allocating memory for this component
    AVFormatContext *pFormatContext = avformat_alloc_context();

    // Open the file and read its header. The codecs are not opened.
    avformat_open_input(&pFormatContext, argv[1], NULL, NULL);

    // Now we have access to some information about our file
    // since we read its header we can say what format (container) it's
    // and some other information related to the format itself.
    printf("format %s, duration %ld us, bit_rate %ld", pFormatContext->iformat->name,
            pFormatContext->duration, pFormatContext->bit_rate);

    // Read Packets from the Format to get stream information
    // this function populates pFormatContext->streams
    // (of size equals to pFormatContext->nb_streams)
    avformat_find_stream_info(pFormatContext, NULL);

    // the component that knows how to encode and decode the stream
    // it's the codec (audio or video)
    AVCodec *pCodec = NULL;

    // this component describes the properties of a codec used by the stream i
    AVCodecParameters *pCodecParameters = NULL;

    int video_stream_index = -1;

    // loop though all the streams and print its main information
    for (int i = 0; i < pFormatContext->nb_streams; i++) {
        AVCodecParameters *pLocalCodecParameters = NULL;
        pLocalCodecParameters = pFormatContext->streams[i]->codecpar;

        AVCodec *pLocalCodec = NULL;

        // finds the registered decoder for a codec ID
        pLocalCodec = avcodec_find_decoder(pLocalCodecParameters->codec_id);

        if (pLocalCodec == NULL) {
            fprintf(stderr, "ERROR unsupported codec!");
            return -1;
        }

        // when the stream is a video we store its index, codec parameters and codec
        if (pLocalCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO) {
            video_stream_index = i;
            pCodec = pLocalCodec;
            pCodecParameters = pLocalCodecParameters;
            printf("Video codec: resolution %d x %d", pLocalCodecParameters->width, pLocalCodecParameters->height);
        }
    }

    AVCodecContext *pCodecContext = avcodec_alloc_context3(pCodec);

    // Fill the codec context based on the values from the supplied codec parameters.
    avcodec_parameters_to_context(pCodecContext, pCodecParameters);

    // Initialize the AVCodecContext to use the given AVCodec.
    avcodec_open2(pCodecContext, pCodec, NULL);

    AVFrame *pFrame = av_frame_alloc();

    AVPacket *pPacket = av_packet_alloc();

    int response = 0;
    int how_many_packets_to_process = 8;

    // fill the Packet with data from the Stream
    while (av_read_frame(pFormatContext, pPacket) >= 0) {
        if (pPacket->stream_index == video_stream_index) {
            response = decode_packet(pPacket, pCodecContext, pFrame);
            if (response < 0)
                break;
            // stop it, otherwise we'll be saving hundreds of frames
            if (--how_many_packets_to_process <= 0)
                break;
        }
        av_packet_unref(pPacket);
    }

    avformat_close_input(&pFormatContext);
    avformat_free_context(pFormatContext);
    av_packet_free(&pPacket);
    av_frame_free(&pFrame);
    avcodec_free_context(&pCodecContext);

    return 0;
}