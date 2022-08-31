// Copyright (c) 2017-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_ARGV_INPUT_HPP
#define TAO_PEGTL_ARGV_INPUT_HPP

#include <cstddef>
#include <sstream>
#include <string>
#include <utility>

#include "eol.hpp"
#include "memory_input.hpp"
#include "tracking_mode.hpp"

namespace tao::pegtl
{
   namespace internal
   {
      [[nodiscard]] inline std::string make_argv_source( const std::size_t argn )
      {
         std::ostringstream oss;
         oss << "argv[" << argn << ']';
         return std::move( oss ).str();
      }

   }  // namespace internal

   template< tracking_mode P = tracking_mode::eager, typename Eol = eol::lf_crlf >
   struct argv_input
      : memory_input< P, Eol >
   {
      template< typename T >
      argv_input( char** argv, const std::size_t argn, T&& in_source )
         : memory_input< P, Eol >( static_cast< const char* >( argv[ argn ] ), std::forward< T >( in_source ) )
      {}

      argv_input( char** argv, const std::size_t argn )
         : argv_input( argv, argn, internal::make_argv_source( argn ) )
      {}
   };

   template< typename... Ts >
   argv_input( Ts&&... ) -> argv_input<>;

}  // namespace tao::pegtl

#endif