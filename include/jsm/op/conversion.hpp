#pragma once

#include <string>
#include <stdexcept>

#include "code.hpp"

namespace jsm
{
  namespace op
  {
    template <typename T = unsigned char>
    T constexpr to_int(code const c)
    { return static_cast<T>(c); }

    inline code constexpr to_code(int const c)
    {
      if(c < to_int<int>(code::nop) || c >= to_int<int>(code::max))
      { throw std::out_of_range{ "invalid code: " + std::to_string(c) }; }
      return static_cast<code>(c);
    }

    template <code C>
    char constexpr const* to_string();
    template <>
    char constexpr const* to_string<code::nop>()
    { return "nop"; }
    template <>
    char constexpr const* to_string<code::halt>()
    { return "halt"; }
    template <>
    char constexpr const* to_string<code::add>()
    { return "add"; }
    template <>
    char constexpr const* to_string<code::sub>()
    { return "sub"; }
    template <>
    char constexpr const* to_string<code::_and>()
    { return "and"; }
    template <>
    char constexpr const* to_string<code::_or>()
    { return "or"; }
    template <>
    char constexpr const* to_string<code::_xor>()
    { return "xor"; }
    template <>
    char constexpr const* to_string<code::_not>()
    { return "not"; }
    template <>
    char constexpr const* to_string<code::_compl>()
    { return "compl"; }
    template <>
    char constexpr const* to_string<code::shl>()
    { return "shl"; }
    template <>
    char constexpr const* to_string<code::shr>()
    { return "shr"; }
    template <>
    char constexpr const* to_string<code::jmp>()
    { return "jmp"; }
    template <>
    char constexpr const* to_string<code::jz>()
    { return "jz"; }
    template <>
    char constexpr const* to_string<code::jnz>()
    { return "jnz"; }
    template <>
    char constexpr const* to_string<code::push>()
    { return "push"; }
    template <>
    char constexpr const* to_string<code::ref>()
    { return "ref"; }
    template <>
    char constexpr const* to_string<code::drop>()
    { return "drop"; }
    template <>
    char constexpr const* to_string<code::dupe>()
    { return "dupe"; }
    template <>
    char constexpr const* to_string<code::store>()
    { return "store"; }
    template <>
    char constexpr const* to_string<code::load>()
    { return "load"; }
    template <>
    char constexpr const* to_string<code::swap>()
    { return "swap"; }
    template <>
    char constexpr const* to_string<code::rol3>()
    { return "rol3"; }
    template <>
    char constexpr const* to_string<code::call>()
    { return "call"; }
    template <>
    char constexpr const* to_string<code::ret>()
    { return "ret"; }

    inline char constexpr const* to_string(code const c)
    {
      switch(c)
      {
        case code::nop:
          return "nop";
        case code::halt:
          return "halt";
        case code::add:
          return "add";
        case code::sub:
          return "sub";
        case code::_and:
          return "and";
        case code::_or:
          return "or";
        case code::_xor:
          return "xor";
        case code::_not:
          return "not";
        case code::_compl:
          return "compl";
        case code::shl:
          return "shl";
        case code::shr:
          return "shr";
        case code::jmp:
          return "jmp";
        case code::jz:
          return "jz";
        case code::jnz:
          return "jnz";
        case code::push:
          return "push";
        case code::ref:
          return "ref";
        case code::drop:
          return "drop";
        case code::dupe:
          return "dupe";
        case code::store:
          return "store";
        case code::load:
          return "load";
        case code::swap:
          return "swap";
        case code::rol3:
          return "rol3";
        case code::call:
          return "call";
        case code::ret:
          return "ret";
        default:
          return "nop";
      }
    }

    inline code to_code(std::string const &str)
    {
      if(str == "nop")
      { return code::nop; }
      else if(str == "halt")
      { return code::halt; }
      else if(str == "add")
      { return code::add; }
      else if(str == "sub")
      { return code::sub; }
      else if(str == "_and")
      { return code::_and; }
      else if(str == "_or")
      { return code::_or; }
      else if(str == "_xor")
      { return code::_xor; }
      else if(str == "_not")
      { return code::_not; }
      else if(str == "_compl")
      { return code::_compl; }
      else if(str == "shl")
      { return code::shl; }
      else if(str == "shr")
      { return code::shr; }
      else if(str == "jmp")
      { return code::jmp; }
      else if(str == "jz")
      { return code::jz; }
      else if(str == "jnz")
      { return code::jnz; }
      else if(str == "push")
      { return code::push; }
      else if(str == "ref")
      { return code::ref; }
      else if(str == "drop")
      { return code::drop; }
      else if(str == "dupe")
      { return code::dupe; }
      else if(str == "store")
      { return code::store; }
      else if(str == "load")
      { return code::load; }
      else if(str == "swap")
      { return code::swap; }
      else if(str == "rol3")
      { return code::rol3; }
      else if(str == "call")
      { return code::call; }
      else if(str == "ret")
      { return code::ret; }
      else
      { return code::nop; }
    }
  }
}
