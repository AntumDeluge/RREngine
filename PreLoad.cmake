# use MSYS generator by default on Windows systems
if (DEFINED WIN32 AND NOT DEFINED CMAKE_GENERATOR)
	message ("Setting generator to MSYS Makefiles")
	set(CMAKE_GENERATOR "MSYS Makefiles" CACHE STRING "")
endif ()
