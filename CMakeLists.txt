cmake_minimum_required(VERSION 3.20)

project(genetic-nn-trainer VERSION 0.1 LANGUAGES CXX)

if(WIN32)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
    include(deploy_qt)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

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
    # if (CMAKE_CXX_COMPILER_ID MATCHES Clang)
        # add_compile_options(-stdlib=libc++)
        # add_link_options(-fuse-ld=lld)
    # endif()
    if (CMAKE_BUILD_TYPE MATCHES Debug)
        add_compile_options(-Og)
    else()
        add_compile_options(-O3)
    endif()
endif()

find_package(QT NAMES Qt6 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)

add_subdirectory(gnnt)
add_subdirectory(view)

target_include_directories(gnnt INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/gnnt>
        $<INSTALL_INTERFACE:include/gnnt
)

set(PROJECT_SOURCES
    main.cpp
    qml.qrc
)
add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

if(WIN32)
    deploy_qt(${PROJECT_NAME})
endif()

target_compile_definitions(${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick gnnt view)

qt_import_qml_plugins(${PROJECT_NAME})
qt_finalize_executable(${PROJECT_NAME})
