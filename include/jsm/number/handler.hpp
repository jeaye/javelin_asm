#pragma once

#include <jsm/handler.hpp>
#include <jsm/op/lookup.hpp>
#include <jsm/number/normalize.hpp>

namespace jsm
{
  namespace number
  {
    inline handler::result handle(std::ofstream &ofs,
                                  std::vector<std::string> const &tokens,
                                  std::size_t const i)
    {
      auto const &token(tokens[i]);

      if(token[0] == '#' || token[0] == '@' ||
         token[0] == '$' || token[0] == '~')
      {
        auto const num(normalize(token));
        ofs << jsm::op::lookup("push") << " " << num << "\n";
        return handler::result{ true, 1, i };
      }
      return handler::result{ false, 0, i };
    }
  }
}
