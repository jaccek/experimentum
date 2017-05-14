cmake_minimum_required(VERSION 2.8.12.2)

set(PROJECT_NAME experimentum)
project(${PROJECT_NAME})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# include directories
include_directories(
	.
	$ENV{WORKSPACE_DIR}/src
	$ENV{WORKSPACE_DIR}/src/mode_api/include
	$ENV{WORKSPACE_DIR}/include

	${OPENGL_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
)

# library directories
link_directories(
	$ENV{WORKSPACE_DIR}/artifacts
)


# files to compile
file(GLOB_RECURSE SRC_FILES
    "*.hpp"
    "*.cpp"
)


add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME}
	Qt5::Widgets
	mode_api
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${CMAKE_DL_LIBS}
)
