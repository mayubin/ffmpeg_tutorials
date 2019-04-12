find_package(PNG REQUIRED)


add_executable(pngtest libpng/pngtest.c)
target_link_libraries(pngtest ${PNG_LIBRARY})