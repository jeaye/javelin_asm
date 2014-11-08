" Language:	Javelin Assembler
" Maintainer:	Jeaye <contact@jeaye.com>

if exists("b:current_syntax")
  finish
endif

let s:cpo_save = &cpo
set cpo&vim

let b:current_syntax = "jsm"

syntax keyword jsm_todo TODO XXX FIXME NOTE
syntax keyword jsm_keyword
      \ nop halt
      \ push pop
      \ mov
      \ cmp jmp je jne jlt jgt
      \ add addc
      \ inc dec
      \ rotl rotr

syntax match jsm_number "\v#<\d+>"
syntax match jsm_hex "\v\$<\d+>"
syntax match jsm_address "\v\@<[0-9,a-f,A-F]+>"
syntax match jsm_register "\<r[a,b,c,d,e,f]\>"
syntax match jsm_label "\v<[a-z_][a-z0-9_]*>:"
syntax match jsm_label "\v:<[a-z_][a-z0-9_]*>"
syntax match jsm_comment "\/\/.*$" contains=jsm_todo
syntax match jsm_comment "\/\*\_.*\*\/" contains=jsm_todo
syntax match jsm_deref "\*"

highlight link jsm_keyword Keyword
highlight link jsm_todo Todo
highlight link jsm_number Number
highlight link jsm_hex Underlined
highlight link jsm_address Include
highlight link jsm_register Structure
highlight link jsm_label Identifier
highlight link jsm_comment Comment
highlight link jsm_deref Delimiter

let &cpo = s:cpo_save
unlet s:cpo_save
