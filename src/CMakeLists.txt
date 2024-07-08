cmake_minimum_required(VERSION 3.16)

set(EXEC ${TARGET_PROJECT})
project(${EXEC})

file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
add_executable(${EXEC} ${SRC} ${HEADERS})

set_property(TARGET ${EXEC} PROPERTY CXX_STANDARD 20)

if(MSVC)
	target_compile_definitions(${EXEC} PUBLIC ${WINDOWS_DEFINES} ${COMMON_DEFINES})
elseif(UNIX AND NOT APPLE)
	target_compile_definitions(${EXEC} PUBLIC ${LINUX_DEFINES} ${COMMON_DEFINES})
endif()

add_library(GLAD ${LIB_GLAD_PATH})

set(COMMON_LIBS glfw3 GLAD glm)
if(UNIX)
	set(OS_LIBS pthread dl)
else()
	set(OS_LIBS)
endif()

target_link_libraries(${EXEC} PUBLIC ${OS_LIBS} ${COMMON_LIBS})

# Copy assets to the binary directory
# add_custom_command(
# 		TARGET ${EXEC} POST_BUILD
# 		COMMAND ${CMAKE_COMMAND} -E remove_directory ${BINARY_OUTPUT_DIR}/assets
# 		COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_PATH} ${BINARY_OUTPUT_DIR}/assets
# )