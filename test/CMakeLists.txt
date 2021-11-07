add_executable(
        tests
        dataset_tests.cpp
        mlp_tests.cpp
)

target_link_libraries(tests PUBLIC gnnt)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/W4)
    if (CMAKE_BUILD_TYPE MATCHES Debug)
        add_compile_options(/O2)
    else()
        add_compile_options(/Od)
    endif()
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wuninitialized -Wshadow -Wunused)
    if (CMAKE_BUILD_TYPE MATCHES Debug)
        add_compile_options(-Og)
    else()
        add_compile_options(-O3)
    endif()
endif()