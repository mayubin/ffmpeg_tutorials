cmake_minimum_required(VERSION 3.12)

project(ffmpeg_tutorials)

# FFmpeg库文件引用
set(FFmpegLIB libavutil.so libavcodec.so libavformat.so libavdevice.so libavfilter.so libswscale.so libswresample.so)

# Pointers On C
add_subdirectory(pointers_on_c)

# FFmpeg官方示例
add_subdirectory(ffmpeg_examples)

# Simple and Fast Multimedia Library
add_subdirectory(sfml)

# cpp官网学习
add_subdirectory(cpp_reference)