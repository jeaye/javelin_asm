#pragma once

#include <jsm/handler.hpp>
#include <jsm/op/lookup.hpp>
#include <jsm/number/normalize.hpp>

namespace jsm
{
  namespace constant
  {
    inline handler::result handle(std::ostream &ofs,
                                  std::vector<std::string> const &tokens,
                                  std::size_t i)
    {
      static std::map<std::string, number::normal> contants;
      auto const &token(tokens[i]);

      if(token[0] == '|') /* Declaration. */
      {
        if(i + 2 >= tokens.size())
        { throw std::runtime_error{ "expected constant name after |" }; }
        if(tokens[i + 1] != "=>")
        {
          throw std::runtime_error
          { "expected => after |; found '" + tokens[i + 1] + "'" };
        }
        contants[tokens[i += 2]] = number::normalize(token.substr(1));
        return handler::result{ true, 0, i };
      }

      auto const var(contants.find(token));
      if(var != contants.end()) /* Reference. */
      {
        ofs << jsm::op::lookup("push") << " " << var->second
          << " // " << token << "\n";
        return handler::result{ true, 1, i };
      }

      return handler::result{ false, 0, i };
    }
  }
}
