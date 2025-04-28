

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	set(RRE_DEBUGGING true)
else()
	set(RRE_DEBUGGING false)
endif()

option(EXAMPLE "Include example game data." OFF)
option(STATIC "Link executable statically." OFF)

# bin2header executable
find_program(BIN2HEADER bin2header)
if(BIN2HEADER)
	set(HAVE_BUILTIN_FONT_MAP true)
else()
	set(HAVE_BUILTIN_FONT_MAP false)
endif()

# ffmpeg executable
find_program(FFMPEG ffmpeg)
