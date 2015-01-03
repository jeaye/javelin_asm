#pragma once

#include <jsm/handler.hpp>
#include <jsm/op/lookup.hpp>

namespace jsm
{
  namespace label
  {
    inline handler::result handle(std::ofstream &ofs,
                                  std::vector<std::string> const &tokens,
                                  std::size_t const i)
    {
      static std::map<std::string, std::string> labels;
      auto const &token(tokens[i]);

      /* Label reference. */
      if(token[0] == ':')
      {
        auto const label(labels.find(token.substr(1)));
        if(label != labels.end())
        {
          ofs << jsm::op::lookup("push") << " " << token << "\n";
          return handler::result{ true, 1, i };
        }
        else
        { throw std::runtime_error{ "unknown label: " + token }; }
      }
      else if(token.back() == ':') /* Label declaration. */
      {
        auto const label(labels.find(token.substr(0, token.size() - 1)));
        if(label != labels.end())
        { throw std::runtime_error{ "label already exists: " + token }; }

        labels[token.substr(0, token.size() - 1)] = "";
        ofs << jsm::op::lookup("nop") << " // " + token << "\n";
        return handler::result{ true, 1, i };
      }

      return handler::result{ false, 0, i };
    }
  }
}
