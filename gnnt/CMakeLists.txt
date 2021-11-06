add_library(gnnt INTERFACE
        gnnt.hpp
        )

target_include_directories(gnnt INTERFACE)
target_link_libraries(gnnt PUBLIC)
