
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(hello_opencv hello_opencv.cpp)
target_link_libraries(hello_opencv ${OpenCV_LIBS})

add_executable(basic_drawing examples/image_processing/basic_drawing.cpp)
target_link_libraries(basic_drawing ${OpenCV_LIBS})
