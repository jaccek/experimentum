cmake_minimum_required(VERSION 2.8.12.2)

set(PROJECT_NAME firlus_playground_mode)
project(${PROJECT_NAME})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $ENV{WORKSPACE_DIR}/artifacts/modes/${PROJECT_NAME})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)


# include directories
include_directories(
	.
	$ENV{WORKSPACE_DIR}/src/firlus/include
	$ENV{WORKSPACE_DIR}/src/mode_api/include
	$ENV{WORKSPACE_DIR}/include
	${GLEW_INCLUDE_DIRS}
	${OPENGL_INCLUDE_DIRS}
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
	firlus
	${GLEW_LIBRARIES}
	${OPENGL_LIBRARIES}
)

add_custom_command(
	TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND cp -ra ${CMAKE_CURRENT_SOURCE_DIR}/shaders ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)
