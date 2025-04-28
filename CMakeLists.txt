
cmake_minimum_required(VERSION 3.21)

# C++ standard
set(CXX_STANDARD_MIN 20)
set(CMAKE_CXX_STANDARD ${CXX_STANDARD_MIN} CACHE STRING "C++ standard to be used")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# enforce minimum C++11 standard compliance
math(EXPR CXX_STANDARD_INT "${CMAKE_CXX_STANDARD}")
if(CXX_STANDARD_INT LESS ${CXX_STANDARD_MIN} OR CXX_STANDARD_INT EQUAL 98)
	message(FATAL_ERROR "Unsupported C++ standard ${CMAKE_CXX_STANDARD}; required is at least C++${CXX_STANDARD_MIN}")
endif()

# NOTE:
# - compiler-specefic extensions is enabled by default
# - may need to enable if GNU specific `readlink` is necessary
set(CMAKE_CXX_EXTENSIONS OFF)


# project & version info

project(RREngine VERSION 0.1.0)
set(RRE_VER_MAJ 0)
set(RRE_VER_MIN 1)
set(RRE_VER_REL 0)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/options.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/depends.cmake")

# configure header file to pass some of the CMake settings to source compiler
configure_file("config.h.in" "config.h")


# compiler options

set(GNUC false)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	set(GNUC true)
	# prioritize Clang over GNU
	find_program(CLANG_COMPILER NAMES clang++)
	if(CLANG_COMPILER)
		set(CMAKE_C_COMPILER_ID "Clang")
		set(CMAKE_C_COMPILER clang)
		set(CMAKE_CXX_COMPILER_ID "Clang")
		set(CMAKE_CXX_COMPILER clang++)
	else()
		set(CMAKE_C_COMPILER_ID "GNU")
		set(CMAKE_C_COMPILER gcc)
		set(CMAKE_CXX_COMPILER_ID "GNU")
		set(CMAKE_CXX_COMPILER g++)
	endif()
endif()


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
	elseif(GNUC)
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

#add_executable(game ${CPP_SOURCE} ${LUA_C_SOURCE})
add_executable(game ${CPP_SOURCE})
target_link_libraries(game PRIVATE ${LINK_LIBRARIES})

# convert or copy built-in resources
file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/builtin/tileset")
if(BIN2HEADER)
	message("-- bin2header found")
	message("-- Converting built-in resources ...")
	execute_process(
		COMMAND "${BIN2HEADER}"
			# bin2header output fails if "-" in path name so output to source dir & move
			#-o "${PROJECT_BINARY_DIR}/builtin/tileset/fontmap.h"
			-o "${PROJECT_SOURCE_DIR}/fontmap_png.h"
			"${PROJECT_SOURCE_DIR}/builtin/tileset/fontmap.png"
	)
	file(COPY "${PROJECT_SOURCE_DIR}/fontmap_png.h" DESTINATION "${PROJECT_BINARY_DIR}/builtin/tileset")
	file(REMOVE "${PROJECT_SOURCE_DIR}/fontmap_png.h")
else()
	message("-- bin2header NOT found")
	file(COPY "${PROJECT_SOURCE_DIR}/builtin/tileset/fontmap.png" DESTINATION "${PROJECT_BINARY_DIR}/data/tileset")
endif()
# config analogous to fontmap.png
file(READ "${PROJECT_SOURCE_DIR}/builtin/conf/fonts.xml" FONTS_CONFIG_IN)
string(REPLACE "\"" "\\\"" FONTS_CONFIG_IN "${FONTS_CONFIG_IN}")
string(REPLACE "\n" "\\n" FONTS_CONFIG_IN "${FONTS_CONFIG_IN}")
set(FONTS_CONFIG_OUT "${PROJECT_BINARY_DIR}/builtin/conf/fonts.h")
file(WRITE "${FONTS_CONFIG_OUT}" "#include <string>\n")
file(APPEND "${FONTS_CONFIG_OUT}"  "const static inline std::string builtin_fonts_config = \"${FONTS_CONFIG_IN}\";\n")


# example game data

if(EXAMPLE)
	# REGEX not working in this copy command
	#~ file(
		#~ COPY "${PROJECT_SOURCE_DIR}/data"
		#~ DESTINATION "${PROJECT_BINARY_DIR}"
		#~ REGEX "^${PROJECT_SOURCE_DIR}/data/music/.*|.*/README\.txt$" EXCLUDE
	#~ )

	set(DATA_DIR_SOURCE "${PROJECT_SOURCE_DIR}/data")
	set(DATA_DIR_TARGET "${PROJECT_BINARY_DIR}/data")

	file(GLOB_RECURSE DATA_FILES RELATIVE "${DATA_DIR_SOURCE}" "${DATA_DIR_SOURCE}/*")
	list(FILTER DATA_FILES EXCLUDE REGEX "^music/*|README.txt$")
	list(FILTER DATA_FILES EXCLUDE REGEX "^template/*")

	foreach(D_FILE ${DATA_FILES})
		cmake_path(GET D_FILE PARENT_PATH D_DIR)
		file(
			COPY "${DATA_DIR_SOURCE}/${D_FILE}"
			DESTINATION "${DATA_DIR_TARGET}/${D_DIR}"
		)
	endforeach()

	file(GLOB_RECURSE MUSIC_SOURCE_FILES RELATIVE "${DATA_DIR_SOURCE}/music" "${DATA_DIR_SOURCE}/music/*.flac")

	if(NOT FFMPEG)
		message("-- WARNING: ffmpeg not found; cannot build example music")
	else()
		message("-- ffmpeg found")
		execute_process(
			COMMAND ${CMAKE_COMMAND} -E echo "Converting audio sources to Ogg/Vorbis ..."
		)
		foreach(MUSIC_FLAC ${MUSIC_SOURCE_FILES})
			string(REGEX REPLACE "\.flac$" ".ogg" MUSIC_OGG "${MUSIC_FLAC}")
			set(MUSIC_OGG_TARGET "${DATA_DIR_TARGET}/music/${MUSIC_OGG}")
			cmake_path(GET MUSIC_OGG_TARGET PARENT_PATH MUSIC_OGG_DIR)
			file(MAKE_DIRECTORY "${MUSIC_OGG_DIR}")

			execute_process(
				COMMAND "${FFMPEG}"
					-y
					-hide_banner
					-loglevel warning
					-i "${DATA_DIR_SOURCE}/music/${MUSIC_FLAC}"
					-c:a libvorbis
					-b:a 96k
					"${MUSIC_OGG_TARGET}"
			)
		endforeach()
	endif()

	message("-- Configured to include example game data")
endif()
