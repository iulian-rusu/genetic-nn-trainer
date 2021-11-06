add_library(model STATIC
        model.cpp
        model.h
        )

target_include_directories(model PUBLIC .)
target_link_libraries(model PRIVATE Qt${QT_VERSION_MAJOR}::Core)
