add_library(model STATIC
        model.cpp
        model.hpp)

target_include_directories(model PUBLIC .)
target_link_libraries(model PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(model PUBLIC gnnt)
