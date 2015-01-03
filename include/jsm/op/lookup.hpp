#pragma once

#include <string>
#include <map>

#include <jsm/op/op.hpp>

namespace jsm
{
  namespace op
  {
    enum class lookup_mode
    {
      binary,
      text
    };

    template <lookup_mode M = lookup_mode::text>
    auto& lookup()
    {
      static std::map<std::string, std::string> ops
      {
        { "nop", { to_int(code::nop) } }, { "halt", { to_int(code::halt) } },
        { "add", { to_int(code::add) } }, { "sub", { to_int(code::sub) } },
        { "and", { to_int(code::_and) } }, { "or", { to_int(code::_or) } },
        { "xor", { to_int(code::_xor) } }, { "not", { to_int(code::_not) } },
        { "compl", { to_int(code::_compl) } },
        { "shl", { to_int(code::shl) } }, { "shr", { to_int(code::shr) } },
        { "jmp", { to_int(code::jmp) } }, { "jz", { to_int(code::jz) } },
        { "jnz", { to_int(code::jnz) } },
        { "push", { to_int(code::push) } }, { "ref", { to_int(code::ref) } },
        { "drop", { to_int(code::drop) } },
        { "dupe", { to_int(code::dupe) } }, { "store", { to_int(code::store) } },
        { "load", { to_int(code::load) } },
        { "swap", { to_int(code::swap) } },
        { "rol3", { to_int(code::rol3) } },
        { "call", { to_int(code::call) } }, { "ret", { to_int(code::ret) } }
      };
      return ops;
    }

    template <>
    auto& lookup<lookup_mode::text>()
    {
      static std::map<std::string, std::string> ops
      {
        { "nop", "op_nop" }, { "halt", "op_halt" },
        { "add", "op_add" }, { "sub", "op_sub" },
        { "and", "op_and" }, { "or", "op_or" },
        { "xor", "op_xor" }, { "not", "op_not" },
        { "compl", "op_compl" },
        { "shl", "op_shl" }, { "shr", "op_shr" },
        { "jmp", "op_jmp" }, { "jz", "op_jz" }, { "jnz", "op_jnz" },
        { "push", "op_push" }, { "ref", "op_ref" }, { "drop", "op_drop" },
        { "dupe", "op_dupe" }, { "store", "op_store" }, { "load", "op_load" },
        { "swap", "op_swap" },
        { "rol3", "op_rol3" },
        { "call", "op_call" }, { "ret", "op_ret" }
      };
      return ops;
    }

    template <lookup_mode M = lookup_mode::text>
    std::string lookup(std::string const &s)
    {
      auto const &table(lookup<M>());
      auto const it(table.find(s));
      if(it == table.end())
      { throw std::runtime_error{ "failed to lookup op: " + s }; }
      return it->second;
    }
  }
}
