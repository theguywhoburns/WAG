cmake_minimum_required(VERSION 3.22)
# Setup WAGInclude dir and a global build dir
project(WAGBuild)
set(WAG_INCLUDE_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/WAG/include")
set(GLM_INCLUDE_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm")
set(GLOBAL_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")
file(MAKE_DIRECTORY ${GLOBAL_BUILD_DIR})
add_subdirectory(WAG)
add_subdirectory(TestBed)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_DEBUG_OUTPUT_DIRECTORY bin)

# Renderers
add_subdirectory(DX12Renderer)
add_subdirectory(VulkanRenderer)