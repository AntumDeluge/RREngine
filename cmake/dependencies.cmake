
# SDL2 library
find_package(SDL2 REQUIRED)

include_directories(
	"include"
	${SDL2_INCLUDE_DIRS}
	# add the binary tree to the search path to include "config.h"
	${PROJECT_BINARY_DIR}
)
