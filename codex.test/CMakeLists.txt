project( codex.test )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../codex/include )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../googletest/googletest/include )

link_directories( ${codex.workspace_BINARY_DIR}/codex )

if( MSVC )
	add_definitions (/D _CRT_SECURE_NO_WARNINGS)
else()
	add_definitions( -Wall -std=c++11 -o2 -g -ggdb )
	if( APPLE )

	else()

	endif()
endif()

add_executable( codex.test
	test_codex.cpp
)

target_link_libraries( codex.test
 codex
 gtest
 gtest_main
)
