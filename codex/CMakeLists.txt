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
    include/codex/diag/error.hpp
    include/codex/allocator.hpp
    include/codex/buffer/ctrl_blk.hpp
    include/codex/buffer/shared_blk.hpp
    include/codex/convenience/time.hpp
    include/codex/convenience/base64.hpp
    include/codex/convenience/crc32.hpp
)

set( SRCS
    src/codex.cpp
    src/diag/error.cpp
    src/allocator.cpp
    src/buffer/ctrl_blk.cpp
    src/buffer/shared_blk.cpp
    src/convenience/time.cpp
    src/convenience/base64.cpp
    src/convenience/crc32.cpp
    )

  add_library( codex STATIC ${HEADERS} ${SRCS} )

if ( CODEX_SHARED )
  add_library( codex.shared SHARED ${HEADERS} ${SRCS} )
endif()
