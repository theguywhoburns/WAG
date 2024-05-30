# Setup WAGInclude dir and a global build dir
set(WAG_INCLUDE_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/WAG/include")
set(GLOBAL_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")
file(MAKE_DIRECTORY ${GLOBAL_BUILD_DIR})
add_subdirectory(WAG)
add_subdirectory(TestBed)