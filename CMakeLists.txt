cmake_minimum_required (VERSION 3.21)

project ("leikljoslinjer")

set (CMAKE_C_STANDARD 17)
set (CMAKE_C_STANDARD_REQUIRED ON)
set	(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set (STB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Dependencies/stb")

set(SOURCE
	"source/main.c"
	"include/util.h"
 "include/linalg.h" "source/linalg.c" "include/geometry.h" "source/geometry.c" "include/scene.h" "source/scene.c" "source/dep_impl.c" "include/image.h" "source/image.c")

add_executable (${PROJECT_NAME} ${SOURCE})

target_include_directories(
	${PROJECT_NAME}
	PUBLIC
	"include"
	${VMA_INCLUDE_DIR}
	${STB_INCLUDE_DIR}
)