

set(C_TESTS
        01_a_quick_start
        10_structures_and_unions
        11_dynamic_memory_allocation
        sort
        strdup
        12_using_structures_and_pointers
        )

foreach(TEST ${C_TESTS})
    add_executable(${TEST} ${TEST}.c)

endforeach(TEST)

