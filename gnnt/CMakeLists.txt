add_library(
        gnnt INTERFACE
        gnnt.hpp
)

add_executable(testingexe
        testing/tests.cpp
)

target_include_directories(gnnt INTERFACE .)
