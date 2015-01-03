#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <stdexcept>

#include <jtl/iterator/stream_delim.hpp>

#include <jsm/op/lookup.hpp>

std::map<std::string, std::string> labels;
std::map<std::string, std::string> contants;

int main(int const argc, char ** const argv)
{
  if(argc != 2)
  {
    std::cerr << "usage: " << argv[0] << " <file>" << std::endl;
    return 1;
  }

  std::cout << "assembling " << argv[1] << std::endl;

  std::ofstream ofs{ "out." + std::string{argv[1]} };

  std::ifstream ifs{ argv[1] };
  std::vector<std::string> tokens;
  std::copy(jtl::it::stream_delim<>{ ifs, " \n" },
            jtl::it::stream_delim<>{}, std::back_inserter(tokens));
  tokens.erase(std::unique(tokens.begin(), tokens.end(),
               [](auto const &lhs, auto const &rhs)
               { return lhs.empty() && rhs.empty(); }), tokens.end());

  std::size_t instructions{};

  for(std::size_t i{}; i < tokens.size(); ++i)
  {
    auto const &token(tokens[i]);
    if(token.empty())
    { continue; }

    /* OP code */
    auto const op(jsm::op::lookup().find(token));
    if(op != jsm::op::lookup().end())
    {
      ofs << op->second << "\n";
      continue;
    }
    
    /* Label reference. */
    if(token[0] == ':')
    {
      auto const label(labels.find(token.substr(1)));
      if(label != labels.end())
      {
        ofs << jsm::op::lookup("push") << " " << token << "\n";
        continue;
      }
      else
      { throw std::runtime_error{ "unknown label: " + token }; }
    }
    /* Label declaration. */
    else if(token.back() == ':')
    {
      auto const label(labels.find(token.substr(0, token.size() - 1)));
      if(label != labels.end())
      { throw std::runtime_error{ "label already exists: " + token }; }

      labels[token.substr(0, token.size() - 1)] = "";
      ofs << jsm::op::lookup("nop") << " // " + token << "\n";
      continue;
    }

    /* Number. */
    if(token[0] == '#' || token[0] == '@' ||
       token[0] == '$' || token[0] == '~')
    {
      ofs << jsm::op::lookup("push") << " " << token << "\n";
      continue;
    }

    /* Constant declaration. */
    if(token[0] == '|')
    {
      if(i + 2 >= tokens.size())
      { throw std::runtime_error{ "expected constant name after |" }; }
      if(tokens[i + 1] != "=>")
      {
        throw std::runtime_error
        { "expected => after |; found '" + tokens[i + 1] + "'" };
      }
      contants[tokens[i += 2]] = token.substr(1);
      continue;
    }
    /* Comment. */
    else if(token.substr(0, 2) == "//")
    {
      for(std::size_t k{ ++i }; k < tokens.size() && !tokens[k].empty(); ++k, ++i)
      { }
      continue;
    }

    /* Constant reference. */
    auto const var(contants.find(token));
    if(var != contants.end())
    {
      ofs << jsm::op::lookup("push") << " " << var->second
          << " // " << token << "\n";
      continue;
    }
    else
    { throw std::runtime_error{ "unknown value: " + token }; }
  }
}
