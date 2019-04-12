
set(FFMPEG_EXAMPLES
        metadata
        decode_video
        )

foreach(TEST ${FFMPEG_EXAMPLES})
    add_executable(${TEST} ${TEST}.c)
    target_link_libraries(${TEST} ${FFmpegLIB} -lm)
endforeach(TEST)