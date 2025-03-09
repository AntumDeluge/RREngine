
# debugging symbols
option(DEBUG "Include debugging symbols" OFF)
if(DEBUG)
	set(RRE_DEBUGGING true)
else()
	set(RRE_DEBUGGING false)
endif()

option(STATIC "Try to link executable statically" OFF)

option(EXAMPLE "Include example game data files" OFF)

# look for bin2header executable
find_program(BIN2HEADER NAMES bin2header)
if(BIN2HEADER)
	set(HAVE_BUILTIN_FONT_MAP true)
else()
	set(HAVE_BUILTIN_FONT_MAP false)
endif()
