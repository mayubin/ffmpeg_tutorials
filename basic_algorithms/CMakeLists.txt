

add_library(crc_model crc_impl/crc_model.c)

# CRC测试
add_executable(crc_test crc_impl/crc_test.c)
target_link_libraries(crc_test crc_model)