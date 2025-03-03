
include(FindPkgConfig)

# SDL2
find_package(SDL2 REQUIRED)
pkg_search_module(SDL2MIXER SDL2_mixer>=2.0.0)
pkg_search_module(SDL2IMAGE SDL2_image>=2.0.0)
# TinyXML-2
pkg_search_module(TINYXML2 tinyxml2)

if(NOT SDL2MIXER_VERSION)
	message(FATAL_ERROR "Please install SDL2_mixer")
endif()

if(NOT SDL2IMAGE_VERSION)
	message(FATAL_ERROR "Please install SDL2_image")
endif()

if(NOT TINYXML2_VERSION)
	message(FATAL_ERROR "Please install tinyxml2")
endif()

# tmxlite
pkg_search_module(TMXLITE tmxlite)
if(NOT TMXLITE_VERSION)
	message(FATAL_ERROR "Required library tmxlite not found")
endif()

# make sure libs get updated
unset(LIBS)
if(NOT STATIC)
	set(LIBS ${SDL2_LIBRARIES} ${TMXLITE_LIBRARIES})
else()
	# FIXME: need portable method of finding static libs
	find_library(LIBSDL2main libSDL2main.a NO_CACHE REQUIRED)
	find_library(LIBSDL2 libSDL2.a NO_CACHE REQUIRED)
	set(LIBS ${LIBSDL2main} ${LIBSDL2})

	if(MINGW)
		set(LIBS ${LIBS} libtmxlite-s.a)
	else()
		set(LIBS ${LIBS} ${TMXLITE_LIBRARIES})
	endif()

	if(WIN32)
		find_library(LIBWINMM libwinmm REQUIRED)
		find_library(LIBCFGMGR libcfgmgr32 REQUIRED)
		find_library(LIBIMM libimm32 REQUIRED)
		find_library(LIBSETUPAPI libsetupapi REQUIRED)
		find_library(LIBVERSION libversion REQUIRED)
		set(LIBS ${LIBS} ${LIBWINMM} ${LIBCFGMGR} ${LIBIMM} ${LIBSETUPAPI} ${LIBVERSION} -mwindows)
	endif()
endif()

set(LIBS ${LIBS} ${SDL2MIXER_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${TINYXML2_LIBRARIES})

include_directories(
	"include"
	${SDL2_INCLUDE_DIRS}
	${SDL2MIXER_INCLUDE_DIRS}
	${SDL2IMAGE_INCLUDE_DIRS}
	"${PROJECT_SOURCE_DIR}/lib/cxxopts"
	# add the binary tree to the search path to include "config.h"
	${PROJECT_BINARY_DIR}
)
