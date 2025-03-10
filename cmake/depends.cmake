
include(FindPkgConfig)

if(STATIC)
	set(MODULE_PARAMS --static)
endif()

# SDL2
# FIXME: determine correct required minimum versions
pkg_search_module(SDL2 sdl2>=2.0.18 ${MODULE_PARAMS})
pkg_search_module(SDL2MIXER SDL2_mixer>=2.0.0 ${MODULE_PARAMS})
pkg_search_module(SDL2IMAGE SDL2_image>=2.0.0 ${MODULE_PARAMS})
if(NOT SDL2MIXER_VERSION)
	message(FATAL_ERROR "Required library SDL2_mixer or compatible version (>=2.0.0) not found")
endif()
if(NOT SDL2IMAGE_VERSION)
	message(FATAL_ERROR "Required library SDL2_image or compatible version (>=2.0.0) not found")
endif()

# TinyXML-2
pkg_search_module(TINYXML2 tinyxml2 ${MODULE_PARAMS})
if(NOT TINYXML2_VERSION)
	message(FATAL_ERROR "Please install tinyxml2")
endif()

# tmxlite
pkg_search_module(TMXLITE tmxlite ${MODULE_PARAMS})
if(NOT TMXLITE_VERSION)
	message(FATAL_ERROR "Required library tmxlite not found")
endif()
if(STATIC AND NOT MSVC)
	# tmxlite static libs may not be configured correctly for pkg-config
	find_library(TMXLITE_A libtmxlite.a NO_CACHE)
	if(NOT TMXLITE_A)
		message("-- WARNING: tmxlite static library may not be configured correctly for pkg-config; attempting to locate manually")
		find_library(TMXLITE_A libtmxlite-s.a NO_CACHE REQUIRED)
		message("-- Found tmxlite static library: ${TMXLITE_A}")
		set(TMXLITE_STATIC_LIBRARIES ${TMXLITE_A})
	endif()
endif()


# compiler include paths

include_directories(
	"include"
	# "config.h" & built-in data
	"${PROJECT_BINARY_DIR}"
	# system libraries
	"${SDL2_INCLUDE_DIRS}"
	"${SDL2MIXER_INCLUDE_DIRS}"
	"${SDL2IMAGE_INCLUDE_DIRS}"
	# bundled libraries
	"${PROJECT_SOURCE_DIR}/lib/cxxopts"
)


# linker libraries

# make sure libs not cached
unset(LIBS)

if(NOT STATIC)
	set(LIBS
		${SDL2_LIBRARIES}
		${SDL2MIXER_LIBRARIES}
		${SDL2IMAGE_LIBRARIES}
		${TINYXML2_LIBRARIES}
		${TMXLITE_LIBRARIES}
	)
else()
	set(LIBS
		${SDL2_STATIC_LIBRARIES}
		${SDL2MIXER_STATIC_LIBRARIES}
		${SDL2IMAGE_STATIC_LIBRARIES}
		${TINYXML2_STATIC_LIBRARIES}
		${TMXLITE_STATIC_LIBRARIES}
	)
endif()
