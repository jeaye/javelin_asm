#pragma once

#include <vector>
#include <string>
#include <functional>
#include <tuple>
#include <cstdint>
#include <ostream>

namespace jsm
{
  namespace handler
  {
    using result = std::tuple<bool, std::size_t, std::size_t>;
    using func = std::function<result (std::ostream &,
                                       std::vector<std::string> const&,
                                       std::size_t)>;
  }
}
