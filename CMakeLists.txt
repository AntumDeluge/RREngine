cmake_minimum_required(VERSION 3.12.4)
project(RREngine)

# version info
set(RREngine_VER_MAJ 0)
set(RREngine_VER_MIN 1)
set(RREngine_VER_REL 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file("config.h.in" "config.h")

include(FindPkgConfig)

# SDL2 library
find_package(SDL2 REQUIRED)
pkg_search_module(SDL2MIXER SDL2_mixer>=2.0.0)
pkg_search_module(SDL2IMAGE SDL2_image>=2.0.0)

if(NOT SDL2MIXER_VERSION)
	message(FATAL_ERROR "Please install SDL2_mixer")
endif()

if(NOT SDL2IMAGE_VERSION)
	message(FATAL_ERROR "Please install SDL2_image")
endif()

include_directories(
	"include"
	${SDL2_INCLUDE_DIRS}
	${SDL2MIXER_INCLUDE_DIRS}
	${SDL2IMAGE_INCLUDE_DIRS}
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

# Windows resources
if(WIN32)
	list(APPEND FLIST "${CMAKE_SOURCE_DIR}/win_resources.rc")
	# the output executable
	#add_executable(game WIN32 ${FLIST})
	add_executable(game ${FLIST})
else()
	# the output executable
	add_executable(game ${FLIST})
endif()

target_link_libraries(game PRIVATE ${SDL2_LIBRARIES} ${SDL2MIXER_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
