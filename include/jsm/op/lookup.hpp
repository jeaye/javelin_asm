#pragma once

#include <string>
#include <map>

#include <jsm/op/conversion.hpp>

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
        { to_string<code::nop>(), { to_int(code::nop) } },
        { to_string<code::halt>(), { to_int(code::halt) } },
        { to_string<code::add>(), { to_int(code::add) } },
        { to_string<code::sub>(), { to_int(code::sub) } },
        { to_string<code::_and>(), { to_int(code::_and) } },
        { to_string<code::_or>(), { to_int(code::_or) } },
        { to_string<code::_xor>(), { to_int(code::_xor) } },
        { to_string<code::_not>(), { to_int(code::_not) } },
        { to_string<code::_compl>(), { to_int(code::_compl) } },
        { to_string<code::shl>(), { to_int(code::shl) } },
        { to_string<code::shr>(), { to_int(code::shr) } },
        { to_string<code::jmp>(), { to_int(code::jmp) } },
        { to_string<code::jz>(), { to_int(code::jz) } },
        { to_string<code::jnz>(), { to_int(code::jnz) } },
        { to_string<code::push>(), { to_int(code::push) } },
        { to_string<code::ref>(), { to_int(code::ref) } },
        { to_string<code::drop>(), { to_int(code::drop) } },
        { to_string<code::dupe>(), { to_int(code::dupe) } },
        { to_string<code::store>(), { to_int(code::store) } },
        { to_string<code::load>(), { to_int(code::load) } },
        { to_string<code::swap>(), { to_int(code::swap) } },
        { to_string<code::rol3>(), { to_int(code::rol3) } },
        { to_string<code::call>(), { to_int(code::call) } },
        { to_string<code::ret>(), { to_int(code::ret) } }
      };
      return ops;
    }

    template <>
    auto& lookup<lookup_mode::text>()
    {
      static std::map<std::string, std::string> ops
      {
        { to_string<code::nop>(), "op_nop" },
        { to_string<code::halt>(), "op_halt" },
        { to_string<code::add>(), "op_add" },
        { to_string<code::sub>(), "op_sub" },
        { to_string<code::_and>(), "op_and" },
        { to_string<code::_or>(), "op_or" },
        { to_string<code::_xor>(), "op_xor" },
        { to_string<code::_not>(), "op_not" },
        { to_string<code::_compl>(), "op_compl" },
        { to_string<code::shl>(), "op_shl" },
        { to_string<code::shr>(), "op_shr" },
        { to_string<code::jmp>(), "op_jmp" },
        { to_string<code::jz>(), "op_jz" },
        { to_string<code::jnz>(), "op_jnz" },
        { to_string<code::push>(), "op_push" },
        { to_string<code::ref>(), "op_ref" },
        { to_string<code::drop>(), "op_drop" },
        { to_string<code::dupe>(), "op_dupe" },
        { to_string<code::store>(), "op_store" },
        { to_string<code::load>(), "op_load" },
        { to_string<code::swap>(), "op_swap" },
        { to_string<code::rol3>(), "op_rol3" },
        { to_string<code::call>(), "op_call" },
        { to_string<code::ret>(), "op_ret" }
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
