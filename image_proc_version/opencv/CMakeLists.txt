
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )


SET(CORE_FUNCTIONALITY_TESTS
        mat
        scan_images
        mask_operations
        image_operations
        blending_two_images
        contrast_brightness
        )
foreach(TEST ${CORE_FUNCTIONALITY_TESTS})
    add_executable(${TEST} examples/core_functionality/${TEST}.cpp)
    target_link_libraries(${TEST} ${OpenCV_LIBS})
endforeach(${TEST})

add_executable(basic_drawing examples/image_processing/basic_drawing.cpp)
target_link_libraries(basic_drawing ${OpenCV_LIBS})
