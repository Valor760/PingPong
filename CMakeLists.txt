cmake_minimum_required(VERSION 3.16)

set(TARGET_PROJECT PingPong)
project(${TARGET_PROJECT})

# Global vars
set(OUTPUT_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/$<1:lib>) # $<1:> to remove Debug/Release subdirs
set(EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external)
set(ASSETS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/assets)
set(LIB_GLAD_PATH ${EXTERNAL_DIR}/glad/gl.c)
set(SHADERS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/shaders)

# Defines
set(WINDOWS_DEFINES "PONG_PLATFORM_WINDOWS" "_CRT_SECURE_NO_WARNINGS")
set(LINUX_DEFINES   "PONG_PLATFORM_LINUX")
set(COMMON_DEFINES  "")

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
if(NOT DEFINED ${CMAKE_BUILD_TYPE})
	set(CMAKE_BUILD_TYPE Debug)
	set(COMMON_DEFINES "${COMMON_DEFINES} PONG_BUILD_DEBUG")
endif()

# Output libs and pdbs to 'lib' dir
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_LIB_DIR})
set(CMAKE_PDB_OUTPUT_DIRECTORY ${OUTPUT_LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_LIB_DIR})
set(BINARY_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)

# GLFW settings
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
if(UNIX AND NOT APPLE)
	set(GLFW_BUILD_WAYLAND ON)
endif()

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:preprocessor /W4")
	# MSVC has weird way to add additional debug/release directory
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/$<1:bin>)
elseif(UNIX AND NOT APPLE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR})
else()
	message(FATAL_ERROR "Current OS is not supported!")
endif()

# Includes
include_directories(${EXTERNAL_DIR}/glfw/include)
include_directories(${EXTERNAL_DIR})
include_directories(${EXTERNAL_DIR}/stb)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/shaders)

# Libraries to link
link_directories(${OUTPUT_LIB_DIR})

add_subdirectory(${EXTERNAL_DIR}/glfw)
add_subdirectory(${EXTERNAL_DIR}/glm)
add_subdirectory(src)