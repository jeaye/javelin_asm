#pragma once

#include <cstdint>
#include <string>
#include <stdexcept>

namespace jsm
{
  namespace number
  {
    using normal = uint64_t;

    namespace detail
    {
      template <std::size_t Base>
      normal parse(std::string const &num)
      { return std::stoull(num, nullptr, Base); }
    }

    inline normal normalize(std::string const &num)
    {
      if(num.empty())
      { throw std::length_error{ "invalid number string length" }; }

      switch(num[0])
      {
        case '~':
          return detail::parse<2>(num.substr(1));
        case '#':
          return detail::parse<10>(num.substr(1));
        case '@':
        case '$':
          return detail::parse<16>(num.substr(1));
        default:
          throw std::runtime_error{ "invalid number: " + num };
      }
    }
  }
}
