//
// Created by wangrl on 19-4-11.
//

#include <stdlib.h>
#include <libavformat/avformat.h>

int main(int argc, char *argv[]) {

    AVFormatContext *fmt_ctx = NULL;
    AVDictionaryEntry *tag = NULL;

    int ret;

    if (argc != 2) {
        printf("usage: %s <input_file>\n"
               "example program to demonstrate the use of the libavformat metadata API.\n"
               "\n", argv[0]);
        return 1;
    }

    /**
     * 通过传入的文件初始化AVFormatContext结构体，该结构体包含很多信息。
     */
    if ((ret == avformat_open_input(&fmt_ctx, argv[1], NULL, NULL)))
        return ret;

    if ((ret = avformat_find_stream_info(fmt_ctx, NULL)) < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot find stream information\n");
        return ret;
    }

    /**
     * 获取元数据信息。
     */
    while (tag = av_dict_get(fmt_ctx->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))
        printf("%s=%s\n", tag->key, tag->value);

    avformat_close_input(&fmt_ctx);

    return EXIT_SUCCESS;
}

