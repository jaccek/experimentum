cmake_minimum_required(VERSION 2.8.12.2)

set(PROJECT_NAME pixelate_mode)
project(${PROJECT_NAME})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $ENV{WORKSPACE_DIR}/artifacts/modes/${PROJECT_NAME})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)


# include directories
include_directories(
	.
	$ENV{WORKSPACE_DIR}/src
	$ENV{WORKSPACE_DIR}/src/mode_api/include
	$ENV{WORKSPACE_DIR}/include
)

# library directories
link_directories(
	$ENV{WORKSPACE_DIR}/artifacts
)


# files to compile
file(GLOB_RECURSE SRC_FILES
    "*.h"
    "*.cpp"
)


add_library(${PROJECT_NAME} SHARED ${SRC_FILES})

target_link_libraries(${PROJECT_NAME}
	mode_api
)
