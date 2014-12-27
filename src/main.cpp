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
  std::copy(jtl::iterator::stream_delim<>{ ifs, ' ' },
            jtl::iterator::stream_delim<>{},
            std::back_inserter(tokens));
  tokens.erase(std::remove_if(tokens.begin(), tokens.end(),
               [](std::string const &s)
               { return s.find_first_not_of(" \t\r\n") == std::string::npos; }),
                tokens.end());
  for(auto const &s : tokens)
  { std::cout << "'" << s << "'\n"; }
}
