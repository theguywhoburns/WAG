cmake_minimum_required(VERSION 3.22)

project(
	WAG
	LANGUAGES CXX
)

find_library(MATH_LIBRARY m REQUIRED)

if(MSVC) 
	add_definitions(/D_CRT_SECURE_NO_WARNINGS) #no warnings shit
	add_definitions(/DWAG_MAJOR=0) 
	add_definitions(/DWAG_MINOR=0) 
	add_definitions(/DWAG_PATCH=1) 
else()
  add_definitions(-D_CRT_SECURE_NO_WARNINGS) #no warnings shit
  add_definitions(-DWAG_MAJOR=0) 
	add_definitions(-DWAG_MINOR=0) 
	add_definitions(-DWAG_PATCH=1) 
endif()

file(GLOB_RECURSE SRC_FILES CMAKE_CONFIGURE_DEPENDS
 "${CMAKE_CURRENT_SOURCE_DIR}/src/*"
 "${CMAKE_CURRENT_SOURCE_DIR}/include/*"
)

add_library(WAG SHARED ${SRC_FILES})
target_compile_definitions(WAG PRIVATE WAG_EXPORT)
target_include_directories(WAG
  PUBLIC
  $<BUILD_INTERFACE:${WAG_INCLUDE_DIR}>
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
  "${GLM_INCLUDE_DIR}"
)

set_property(TARGET WAG PROPERTY C_STANDARD 17)
set_property(TARGET WAG PROPERTY C_STANDARD_REQUIRED ON)

set_target_properties(WAG PROPERTIES OUTPUT_NAME "WAG")
set(CMAKE_BINARY_DIR "${GLOBAL_BUILD_DIR}/")
set_target_properties(WAG PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY "${GLOBAL_BUILD_DIR}/"
  RUNTIME_OUTPUT_DIRECTORY "${GLOBAL_BUILD_DIR}/"
  ARCHIVE_OUTPUT_DIRECTORY "${GLOBAL_BUILD_DIR}/"
	DEBUG_OUTPUT_DIRECTORY "${GLOBAL_BUILD_DIR}/"
  PDB_OUTPUT_DIRECTORY "${GLOBAL_BUILD_DIR}/"
)
target_compile_definitions(WAG PRIVATE PPC_EXPORT)
target_link_libraries(WAG ${MATH_LIBRARY})