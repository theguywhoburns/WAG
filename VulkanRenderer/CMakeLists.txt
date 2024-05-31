cmake_minimum_required(VERSION 3.22)

project(
	VulkanRenderer
	LANGUAGES CXX
)

if(MVSC) 
	add_definitions(-D_CRT_SECURE_NO_WARNINGS) #no warnings shit
endif()

file(GLOB_RECURSE SRC_FILES CMAKE_CONFIGURE_DEPENDS
 "${CMAKE_CURRENT_SOURCE_DIR}/src/*"
 "${CMAKE_CURRENT_SOURCE_DIR}/include/*"
)

set(CMAKE_BINARY_DIR "${GLOBAL_BUILD_DIR}/")

find_package(Vulkan REQUIRED)

add_library(VulkanRenderer SHARED ${SRC_FILES})

target_include_directories(VulkanRenderer
  PUBLIC
  $<BUILD_INTERFACE:${WAG_INCLUDE_DIR}>
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
  "${Vulkan_INCLUDE_DIRS}"
)

target_link_libraries(VulkanRenderer Vulkan::Vulkan)

target_compile_definitions(VulkanRenderer PRIVATE RENDERER_EXPORTS)

set_target_properties(VulkanRenderer PROPERTIES OUTPUT_NAME "VulkanRenderer")

set_target_properties(VulkanRenderer PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY "${GLOBAL_BUILD_DIR}/"
  RUNTIME_OUTPUT_DIRECTORY "${GLOBAL_BUILD_DIR}/"
  ARCHIVE_OUTPUT_DIRECTORY "${GLOBAL_BUILD_DIR}/"
	DEBUG_OUTPUT_DIRECTORY "${GLOBAL_BUILD_DIR}/"
  PDB_OUTPUT_DIRECTORY "${GLOBAL_BUILD_DIR}/"
)
