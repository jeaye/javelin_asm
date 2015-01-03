#pragma once

#include <jsm/handler.hpp>
#include <jsm/op/lookup.hpp>

namespace jsm
{
  namespace op
  {
    inline handler::result handle(std::ofstream &ofs,
                                  std::vector<std::string> const &tokens,
                                  std::size_t const i)
    {
      auto const op(jsm::op::lookup().find(tokens[i]));
      if(op != jsm::op::lookup().end())
      {
        ofs << op->second << "\n";
        return handler::result{ true, 1, i };
      }
      return handler::result{ false, 1, i };
    }
  }
}
