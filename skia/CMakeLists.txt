
include_directories(include/)
include_directories(tools/)

add_library(skia
        src/codec/SkCodec.cpp

        tools/flags/CommandLineFlags.cpp
        )

add_executable(skia_test tests/skia_test.cpp)
target_link_libraries(skia_test skia)