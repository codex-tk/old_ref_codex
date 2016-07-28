CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )


include_directories( /usr/local/include )
link_directories( /usr/local/lib )

if(MSVC)

	add_compile_options("/wd4819")
	add_compile_options("/wd4127")
	foreach (flag_var
				 CMAKE_CXX_FLAGS
				 CMAKE_CXX_FLAGS_DEBUG
				 CMAKE_CXX_FLAGS_RELEASE
				 CMAKE_CXX_FLAGS_MINSIZEREL
				 CMAKE_CXX_FLAGS_RELWITHDEBINFO)
			string(REPLACE "/MD" "-MT" ${flag_var} "${${flag_var}}")
			string(REPLACE "/W3" "/W4" ${flag_var} "${${flag_var}}")
	endforeach()

	string(REGEX REPLACE "/O2" "Od"
			CMAKE_CXX_FLAGS_DEBUG
			"${CMAKE_CXX_FLAGS_DEBUG}")
else()
	add_definitions( -Wall -std=c++11 -o2 -g -ggdb )
endif()

project( asio_echo_server )

if( MSVC )
	add_definitions (/D _CRT_SECURE_NO_WARNINGS)
else()
	add_definitions( -Wall -std=c++11 -o2 -g -ggdb )
	if( APPLE )

	else()

	endif()
endif()

add_executable( asio_echo_server  
  main.cpp
)

target_link_libraries( asio_echo_server
  boost_system
  )
