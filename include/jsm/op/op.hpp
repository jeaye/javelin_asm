#pragma once

#include <string>
#include <map>

namespace jsm
{
  namespace op
  {
    enum class code
    {
      nop, halt,
      add, sub,
      _and, _or, _xor,
      _not, _compl,
      shl, shr,
      jmp, jz, jnz,
      push, ref, drop, dupe,
      store, load, swap,
      rol3,
      call, ret
    };

    template <typename T = unsigned char>
    T constexpr to_int(code const c)
    { return static_cast<T>(c); }
  }
}
