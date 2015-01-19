#pragma once

#include <cstdint>

namespace jsm
{
  namespace op
  {
    enum class code : int64_t
    {
      /* 0x00 */ nop,
      /* 0x01 */ halt,
      /* 0x02 */ add,
      /* 0x03 */ sub,
      /* 0x04 */ _and,
      /* 0x05 */ _or,
      /* 0x06 */ _xor,
      /* 0x07 */ _not,
      /* 0x08 */ _compl,
      /* 0x09 */ shl,
      /* 0x0A */ shr,
      /* 0x0B */ jmp,
      /* 0x0C */ jz,
      /* 0x0D */ jnz,
      /* 0x0E */ push,
      /* 0x0F */ ref,
      /* 0x10 */ drop,
      /* 0x01 */ dupe,
      /* 0x02 */ store,
      /* 0x03 */ load,
      /* 0x04 */ swap,
      /* 0x05 */ rol3,
      /* 0x06 */ call,
      /* 0x07 */ ret,
      max
    };
  }
}
