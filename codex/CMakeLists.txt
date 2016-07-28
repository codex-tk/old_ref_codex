project( codex )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../codex/include )

if ( MSVC )
    set( PLATFORM_DEPEND_HEADERS

    )
    set( PLATFORM_DEPEND_SRCS

    )
else()
  if ( APPLE )
    set( PLATFORM_DEPEND_HEADERS

    )
    set( PLATFORM_DEPEND_SRCS

    )
  else()
    set( PLATFORM_DEPEND_HEADERS

    )
    set( PLATFORM_DEPEND_SRCS

    )
  endif()
	  set( PLATFORM_DEPEND_HEADERS
        ${PLATFORM_DEPEND_HEADERS}
    )
    set( PLATFORM_DEPEND_SRCS
        ${PLATFORM_DEPEND_SRCS}

         )
endif()

set( HEADERS
    include/codex/predefs.hpp
    include/codex/codex.hpp
)

set( SRCS
    src/codex.cpp

    )

  add_library( codex STATIC ${HEADERS} ${SRCS} )

if ( CODEX_SHARED )
  add_library( codex.shared SHARED ${HEADERS} ${SRCS} )
endif()
