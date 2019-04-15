find_package(PNG REQUIRED)


add_executable(png_to_png libpng/png_to_png.c)
target_link_libraries(png_to_png ${PNG_LIBRARY})

find_package(WebP REQUIRED)
include_directories(${WebP_INCLUDE_DIRS})

# WebP_LIBRARIES
add_executable(webpinfo libwebp/webinfo.c)
target_link_libraries(webpinfo "/usr/local/lib/libwebpmux.so" "/usr/local/lib/libwebpdecoder.so" -lm)