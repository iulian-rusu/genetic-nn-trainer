add_library(thirdparty STATIC
        gnnt.hpp
        )

target_include_directories(thirdparty PUBLIC)
target_link_libraries(thirdparty PUBLIC)
