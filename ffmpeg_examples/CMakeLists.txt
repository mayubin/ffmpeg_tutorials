
set(FFMPEG_EXAMPLES
        metadata
        decode_video
        encode_video
        scaling_video
        filtering_video
        hw_decode
        remuxing
        animate_webp_encoder
        transcoding
        muxing
        encode_audio
        transcode_aac
        encode_mp3_to_video
        )

foreach(TEST ${FFMPEG_EXAMPLES})
    add_executable(${TEST} ${TEST}.c)
    target_link_libraries(${TEST} ${FFmpegLIB} -lm)
endforeach(TEST)