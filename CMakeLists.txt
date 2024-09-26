cmake_minimum_required(VERSION 3.22)
# Setup WAGInclude dir and a global build dir
project(WAGBuild)
set(WAG_INCLUDE_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/WAG/include")
set(GLM_INCLUDE_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm")
set(GLOBAL_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")
file(MAKE_DIRECTORY ${GLOBAL_BUILD_DIR})

add_subdirectory(WAG)
add_subdirectory(TestBed)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_DEBUG_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Renderers
add_custom_target(VulkanRenderer ALL
  COMMAND make -f ${CMAKE_CURRENT_SOURCE_DIR}/VulkanRenderer/build.mk all -C ${CMAKE_CURRENT_SOURCE_DIR}/VulkanRenderer
  BYPRODUCTS VulkanRenderer/bin/VulkanRenderer
  VERBATIM)
