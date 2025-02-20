cmake_minimum_required(VERSION 3.12)
project(RREngine)

# version info
set(RREngine_VER_MAJ 0)
set(RREngine_VER_MIN 1)
set(RREngine_VER_REL 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file("config.h.in" "config.h")

# SDL2 library
find_package(SDL2 REQUIRED)

include_directories(
	"include"
	${SDL2_INCLUDE_DIRS}
	# add the binary tree to the search path to include "config.h"
	${PROJECT_BINARY_DIR}
)

# include all source files in compile command
file(GLOB children RELATIVE "${PROJECT_SOURCE_DIR}/src/" "${PROJECT_SOURCE_DIR}/src/*.cpp")
set(FLIST "")
foreach(child ${children})
	if (EXISTS "${PROJECT_SOURCE_DIR}/src/${child}")
		list (APPEND FLIST "src/${child}")
	endif()
endforeach()

# the output executable
add_executable(game ${FLIST})

target_link_libraries(game ${SDL2_LIBRARIES})
