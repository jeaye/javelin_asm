#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

#include <jtl/iterator/stream_delim.hpp>

int main(int const argc, char ** const argv)
{
  if(argc != 2)
  {
    std::cerr << "usage: " << argv[0] << " <file>" << std::endl;
    return 1;
  }

  std::cout << "assembling " << argv[1] << std::endl;

  std::ifstream ifs{ argv[1] };
  std::vector<std::string> tokens;
  std::copy(jtl::it::stream_delim<>{ ifs, " \n" },
            jtl::it::stream_delim<>{}, std::back_inserter(tokens));
  tokens.erase(std::unique(tokens.begin(), tokens.end(),
               [](auto const &lhs, auto const &rhs)
               { return lhs.empty() && rhs.empty(); }), tokens.end());

  for(auto const &s : tokens)
  { std::cout << "'" << s << "'\n"; }
}
