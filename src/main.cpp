#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <stdexcept>

#include <jtl/iterator/stream_delim.hpp>

#include <jsm/op/handler.hpp>
#include <jsm/label/handler.hpp>
#include <jsm/number/handler.hpp>
#include <jsm/constant/handler.hpp>
#include <jsm/comment/handler.hpp>

int main(int const argc, char ** const argv)
{
  if(argc != 2)
  {
    std::cerr << "usage: " << argv[0] << " <file>" << std::endl;
    return 1;
  }

  std::cout << "assembling " << argv[1] << std::endl;

  std::ofstream ofs{ "out." + std::string{argv[1]} };

  /* Tokenize. */
  std::ifstream ifs{ argv[1] };
  std::vector<std::string> tokens;
  std::copy(jtl::it::stream_delim<>{ ifs, " \n" },
            jtl::it::stream_delim<>{}, std::back_inserter(tokens));
  tokens.erase(std::unique(tokens.begin(), tokens.end(),
               [](auto const &lhs, auto const &rhs)
               { return lhs.empty() && rhs.empty(); }), tokens.end());

  /* TODO: make_array in jtl */
  std::vector<jsm::handler::func> handlers
  {
    &jsm::op::handle,
    &jsm::label::handle,
    &jsm::number::handle,
    &jsm::comment::handle,
    &jsm::constant::handle
  };

  std::size_t instructions{};
  for(std::size_t i{}; i < tokens.size(); ++i)
  {
    auto const &token(tokens[i]);
    if(token.empty())
    { continue; }

    bool handled{};
    for(auto const &handler : handlers)
    {
      std::size_t new_instructions{};
      std::tie(handled, new_instructions, i) = handler(ofs, tokens, i);
      instructions += new_instructions;
      if(handled)
      { break; }
    }

    if(!handled)
    { throw std::runtime_error{ "unknown value: " + token }; }
  }
  std::cout << "instructions: " << instructions << std::endl;
}
