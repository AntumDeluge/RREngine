
# debugging symbols
if(DEBUG)
	set(RRE_DEBUGGING true)
else()
	set(RRE_DEBUGGING false)
endif()

set(STATIC "ON" CACHE BOOL "Try to link executable statically")

set(EXAMPLE "OFF" CACHE BOOL "Include example game data files")
