

add_executable(unique_ptr_test unique_ptr_test.cpp)

add_executable(shared_ptr_test shared_ptr_test.cpp)
target_link_libraries(shared_ptr_test -lpthread)

add_executable(weak_ptr_test weak_ptr_test.cpp)
add_executable(allocator_test allocator_test.cpp)

add_executable(lvalue_rvalue_teset lvalue_rvalue_teset.cpp)