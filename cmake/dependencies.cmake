
find_package(SDL2 REQUIRED)

# make sure libs get updated
unset(LIBS)
if(NOT STATIC)
	set(LIBS ${SDL2_LIBRARIES})
else()
	# FIXME: need portable method of finding static libs
	find_library(LIBSDL2main libSDL2main.a NO_CACHE REQUIRED)
	find_library(LIBSDL2 libSDL2.a NO_CACHE REQUIRED)
	set(LIBS ${LIBSDL2main} ${LIBSDL2})

	if(WIN32)
		find_library(LIBWINMM libwinmm REQUIRED)
		find_library(LIBCFGMGR libcfgmgr32 REQUIRED)
		find_library(LIBIMM libimm32 REQUIRED)
		find_library(LIBSETUPAPI libsetupapi REQUIRED)
		find_library(LIBVERSION libversion REQUIRED)
		set(LIBS ${LIBS} ${LIBWINMM} ${LIBCFGMGR} ${LIBIMM} ${LIBSETUPAPI} ${LIBVERSION} -mwindows)
	endif()
endif()

include_directories(
	"include"
	${SDL2_INCLUDE_DIRS}
	# add the binary tree to the search path to include "config.h"
	${PROJECT_BINARY_DIR}
)
