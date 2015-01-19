#pragma once

#include <jsm/handler.hpp>
#include <jsm/op/lookup.hpp>

namespace jsm
{
  namespace comment
  {
    inline handler::result handle(std::ostream &,
                                  std::vector<std::string> const &tokens,
                                  std::size_t i)
    {

      if(tokens[i].size() >= 2 && tokens[i].substr(0, 2) == "//")
      {
        for(std::size_t k{ ++i }; k < tokens.size() && !tokens[k].empty(); ++k, ++i)
        { }
        return handler::result{ true, 0, i };
      }

      return handler::result{ false, 0, i };
    }
  }
}
