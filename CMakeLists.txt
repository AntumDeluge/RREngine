cmake_minimum_required(VERSION 3.12.4)
project(RREngine)

# version info
set(RREngine_VER_MAJ 0)
set(RREngine_VER_MIN 1)
set(RREngine_VER_REL 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file("config.h.in" "config.h")

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/options.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/dependencies.cmake")

if(STATIC)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()

# include all source files in compile command
file(GLOB children RELATIVE "${PROJECT_SOURCE_DIR}/src/" "${PROJECT_SOURCE_DIR}/src/*.cpp")
set(FLIST "")
foreach(child ${children})
	if(EXISTS "${PROJECT_SOURCE_DIR}/src/${child}")
		list(APPEND FLIST "src/${child}")
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

target_link_libraries(game PRIVATE ${LIBS})
