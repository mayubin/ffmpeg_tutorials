
set(FFMPEG_EXAMPLES
        metadata
        decode_video
        encode_video
        scaling_video
        filtering_video
        hw_decode
        )

foreach(TEST ${FFMPEG_EXAMPLES})
    add_executable(${TEST} ${TEST}.c)
    target_link_libraries(${TEST} ${FFmpegLIB} -lm)
endforeach(TEST)