cmake_minimum_required(VERSION 2.8.12.2)

set(PROJECT_NAME mode_api)
project(${PROJECT_NAME})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $ENV{WORKSPACE_DIR}/artifacts)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)

# include directories
include_directories(
	.
	include
	$ENV{WORKSPACE_DIR}/src
	$ENV{WORKSPACE_DIR}/include
)

# library directories
# link_directories(
# )


# files to compile
file(GLOB_RECURSE SRC_FILES
    "*.hpp"
    "*.cpp"
)

add_library(${PROJECT_NAME} SHARED ${SRC_FILES})

target_link_libraries(${PROJECT_NAME}
	Qt5::Widgets
)
