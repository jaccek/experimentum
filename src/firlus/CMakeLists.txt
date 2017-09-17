cmake_minimum_required(VERSION 2.8.12.2)

set(PROJECT_NAME firlus)
project(${PROJECT_NAME})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $ENV{WORKSPACE_DIR}/artifacts)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# include directories
include_directories(
	./include
	$ENV{WORKSPACE_DIR}/include
	${GLEW_INCLUDE_DIRS}
	${OPENGL_INCLUDE_DIRS}
)

# library directories
link_directories(
	$ENV{WORKSPACE_DIR}/libs
)


# files to compile
file(GLOB_RECURSE SRC_FILES
    "*.h"
    "*.cpp"
)


add_library(${PROJECT_NAME} SHARED ${SRC_FILES})

target_link_libraries(${PROJECT_NAME}
	${GLEW_LIBRARIES}
	${OPENGL_LIBRARIES}
)
