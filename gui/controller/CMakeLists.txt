add_library(controller STATIC
        controller.cpp
        controller.hpp
        )

target_include_directories(controller PUBLIC .)
target_link_libraries(controller PRIVATE Qt${QT_VERSION_MAJOR}::Core model)
