
# debugging symbols
option(DEBUG "Include debugging symbols" OFF)
if(DEBUG)
	set(RRE_DEBUGGING true)
else()
	set(RRE_DEBUGGING false)
endif()

option(STATIC "Try to link executable statically" OFF)

option(EXAMPLE "Include example game data files" OFF)
