#pragma once

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
      store, load,
      swap, rol3,
      call, ret
    };
  }
}
