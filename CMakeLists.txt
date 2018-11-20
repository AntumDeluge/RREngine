cmake_minimum_required (VERSION 3.12)
project (RREngine)

# version info
set (RREngine_VER_MAJ 0)
set (RREngine_VER_MIN 1)
set (RREngine_VER_REL 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file ("config.h.in" "config.h")

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

# the output executable
add_executable (game src/main.cpp)
