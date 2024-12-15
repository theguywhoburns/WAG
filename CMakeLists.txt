cmake_minimum_required(VERSION 3.22)
project(WAGProjectManager
    VERSION 1.0.0
    DESCRIPTION "All WAG Projects"
)

set(GLOBAL_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/out")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${GLOBAL_OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${GLOBAL_OUTPUT_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${GLOBAL_OUTPUT_DIR}")

set(WAG_ENGINE_NAME "WAG")
set(WAG_ENGINE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Engine/include")

add_subdirectory("Engine")
add_subdirectory("Editor")
add_subdirectory("Tests")

#add_subdirectory("App")
