CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

project( boost_log.workspace )

if(MSVC)

	set(BOOST_ROOT "D:/tk/work/local/boost_1_61_0")
	set(Boost_USE_STATIC_LIBS   	ON)
	set(Boost_USE_MULTITHREADED 	ON)
	set(Boost_USE_STATIC_RUNTIME  ON)

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

	add_definitions (/D _CRT_SECURE_NO_WARNINGS)
else()
  set(Boost_USE_MULTITHREADED 	OFF)
	add_definitions( -Wall -std=c++11 -o2 -g -ggdb )
endif()

find_package (Boost 1.61.0 REQUIRED COMPONENTS log )
find_package (Threads)

if (Boost_FOUND)
  include_directories (SYSTEM ${Boost_INCLUDE_DIR})
endif()

add_executable( boost_log 
  main.cpp
)

target_link_libraries( boost_log 
  ${Boost_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
  )
