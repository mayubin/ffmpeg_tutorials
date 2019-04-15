find_package(PNG REQUIRED)


add_executable(png_to_png libpng/png_to_png.c)
target_link_libraries(png_to_png ${PNG_LIBRARY})