cmake_minimum_required(VERSION 3.2)

add_executable(
    allocator

    main.cpp
)

set_target_properties(
    allocator

    PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)
