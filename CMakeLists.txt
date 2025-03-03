
cmake_minimum_required(VERSION 3.12.4)
project(RREngine)

# TODO:
# - strip binaries
# - ensure building with at least C++17

# version info
set(RREngine_VER_MAJ 0)
set(RREngine_VER_MIN 1)
set(RREngine_VER_REL 0)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/options.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/depends.cmake")

# configure header file to pass some of the CMake settings to source compiler
configure_file("config.h.in" "config.h")


# linker options

# set executable subsystem to GUI on Win32
if(MSVC)
	set(CMAKE_EXE_LINKER_FLAGS "/SUBSYSTEM:WINDOWS")
elseif(WIN32)
	set(CMAKE_EXE_LINKER_FLAGS "-mwindows")
endif()

if(STATIC)
	if(MSVC)
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STATIC")
	else()
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
	endif()
endif()


# the output executable

# detect all .cpp source files dynamically
file(GLOB_RECURSE CPP_SOURCE "${PROJECT_SOURCE_DIR}/src/*.cpp")
if(WIN32)
	# Windows resources
	list(APPEND CPP_SOURCE "${PROJECT_SOURCE_DIR}/win_resources.rc")
endif()

add_executable(game ${CPP_SOURCE})
target_link_libraries(game PRIVATE ${LIBS})


# example game data

if(EXAMPLE)
	message("-- Configuring to including example game data")

	# TODO: exclude .flac audio source files
	file(
		COPY "${PROJECT_SOURCE_DIR}/data"
		DESTINATION "${PROJECT_BINARY_DIR}"
	)

	find_program(FFMPEG_EXE ffmpeg)
	if(NOT FFMPEG_EXE)
		message("-- WARNING: ffmpeg executable not found")
	else()
		message("-- ffmpeg executable found")
		execute_process(
			COMMAND ffmpeg
				-y
				-i "${PROJECT_SOURCE_DIR}/data/music/summer_sunday.flac"
				-c:a libvorbis
				-b:a 96k
				"${PROJECT_BINARY_DIR}/data/music/summer_sunday.ogg"
		)
	endif()
endif()
