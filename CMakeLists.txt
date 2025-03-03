
cmake_minimum_required(VERSION 3.12.4)

# C++ standard
set(CMAKE_CXX_STANDARD 11 CACHE STRING "C++ standard to be used")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# enforce at least C++11 compliance
math(EXPR CXX_STANDARD_INT "${CMAKE_CXX_STANDARD}")
if(CXX_STANDARD_INT LESS 11 OR CXX_STANDARD_INT EQUAL 98)
	message(FATAL_ERROR "Unsupported C++ standard ${CMAKE_CXX_STANDARD}; required is at least C++11")
endif()

# NOTE:
# - compiler-specefic extensions is enabled by default
# - to disable GNU specific `readlink` should be abandoned
set(CMAKE_CXX_EXTENSIONS ON)


# project & version info

project(RREngine)
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

if(NOT DEBUG)
	# strip executable of debugging symbols
	add_custom_command(
		TARGET game POST_BUILD
		COMMAND ${CMAKE_OBJCOPY} --strip-debug "$<TARGET_FILE:game>"
	)
endif()


# example game data

if(EXAMPLE)
	# TODO: exclude .flac audio source files
	file(
		COPY "${PROJECT_SOURCE_DIR}/data"
		DESTINATION "${PROJECT_BINARY_DIR}"
	)

	find_program(FFMPEG_EXE ffmpeg)
	if(NOT FFMPEG_EXE)
		message("-- WARNING: ffmpeg executable not found; cannot build example music")
	else()
		message("-- ffmpeg executable found")
		add_custom_command(
			TARGET game POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E echo "Converting audio source to Ogg/Vorbis ..."
			COMMAND "${FFMPEG_EXE}"
				-y
				-i "${PROJECT_SOURCE_DIR}/data/music/summer_sunday.flac"
				-c:a libvorbis
				-b:a 96k
				"${PROJECT_BINARY_DIR}/data/music/summer_sunday.ogg"
		)
	endif()

	message("-- Configured to include example game data")
endif()
