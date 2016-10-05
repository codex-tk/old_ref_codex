/*!
 */
#ifndef __codex_mux_h__
#define __codex_mux_h__

#include <codex/codex.hpp>

#if defined( __codex_win32__ )
#include <codex/mux/iocp.hpp>
#include <codex/mux/rio.hpp>
#elif defined( __codex_linux__ )
#include <codex/mux/epoll.hpp>
#elif defined( __codex_apple__ )
#include <codex/mux/kqueue.hpp>
#endif

namespace codex { namespace mux {

#if defined( __codex_win32__ )
  typedef iocp implementation;
#elif defined( __codex_linux__ )
  typedef epoll implementation;
#elif defined( __codex_apple__ )
  typedef kqueue implementation;
#endif

}}

#endif
