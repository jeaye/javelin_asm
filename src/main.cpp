#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <stdexcept>

#include <jtl/iterator/stream_delim.hpp>

std::map<std::string, std::string> ops
{
  { "nop", "nop" }, { "halt", "halt" },
  { "add", "add" }, { "sub", "sub" },
  { "and", "and" }, { "or", "or" }, { "xor", "xor" }, { "not", "not" },
  { "compl", "compl" },
  { "shl", "shl" }, { "shr", "shr" },
  { "jmp", "jmp" }, { "jz", "jz" }, { "jnz", "jnz" },
  { "push", "push" }, { "ref", "ref" }, { "drop", "drop" },
  { "dupe", "dupe" }, { "store", "store" }, { "load", "load" },
  { "swap", "swap" },
  { "rol3", "rol3" },
  { "call", "call" }, { "ret", "ret" }
};

std::map<std::string, std::string> labels;
std::map<std::string, std::string> variables;

int main(int const argc, char ** const argv)
{
  if(argc != 2)
  {
    std::cerr << "usage: " << argv[0] << " <file>" << std::endl;
    return 1;
  }

  std::cout << "assembling " << argv[1] << std::endl;

  std::ofstream ofs{ std::string{argv[1]} + ".out" };

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
    auto const op(ops.find(token));
    if(op != ops.end())
    {
      ofs << op->second << "\n";
      continue;
    }
    
    /* Label declaration of reference. */
    if(token[0] == ':')
    {
      auto const label(labels.find(token.substr(1)));
      if(label != labels.end())
      {
        ofs << token << " push" << "\n";
        continue;
      }
      else
      { throw std::runtime_error{ "unknown label: " + token }; }
    }
    else if(token.back() == ':')
    {
      auto const label(labels.find(std::string{ token.begin(), token.end() - 1 }));
      if(label != labels.end())
      { throw std::runtime_error{ "label already exists: " + token }; }
      labels[std::string{ token.begin(), token.end() - 1 }] = "";
      ofs << "nop // " + token << "\n";
      continue;
    }

    /* Number. */
    if(token[0] == '#' || token[0] == '@' ||
       token[0] == '$' || token[0] == '~')
    {
      ofs << token << " push\n";
      continue;
    }

    /* Constant declaration. */
    if(token[0] == '|')
    {
      if(i + 2 >= tokens.size())
      { throw std::runtime_error{ "expected variable name after |" }; }
      if(tokens[i + 1] != "=>")
      {
        throw std::runtime_error
        { "expected => after |; found '" + tokens[i + 1] + "'" };
      }
      variables[tokens[i += 2]] = token.substr(1);
      continue;
    }
    /* Comment. */
    else if(token.substr(0, 2) == "//")
    {
      for(std::size_t k{ ++i };
          k < tokens.size() && !tokens[k].empty();
          ++k, ++i)
      { }
      continue;
    }

    /* Constant reference. */
    auto const var(variables.find(token));
    if(var != variables.end())
    {
      ofs << var->second << " push" << " # " << token << "\n";
      continue;
    }
    else
    { throw std::runtime_error{ "unknown value: " + token }; }
  }
}
