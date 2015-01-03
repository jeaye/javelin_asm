" Language: Javelin Assembly
" Maintainer:	Jeaye <contact@jeaye.com>

let s:cpo_save = &cpo
set cpo&vim

let b:current_syntax = "jsm"

syntax keyword jsm_todo TODO XXX FIXME NOTE
syntax keyword jsm_keyword
      \ nop halt
      \ add sub
      \ and or xor
      \ not compl
      \ shl shr
      \ jmp jz jnz
      \ push ref drop dupe
      \ store load swap
      \ rol3
      \ call ret

syntax match jsm_number "\v#<\d+>"
syntax match jsm_hex "\v\$<\d+>"
syntax match jsm_binary "\v\~<\d+>"
syntax match jsm_address "\v\@<[0-9,a-f,A-F]+>"

syntax match jsm_ref_delim "[\*,\&]"

syntax match jsm_name_delim " | "
syntax match jsm_name "\v<[a-z_][a-z0-9_]*>"
syntax match jsm_label_delim ":"
syntax match jsm_label "\v<[a-z_][a-z0-9_]*>:" contains=jsm_label_delim
syntax match jsm_label "\v:<[a-z_][a-z0-9_]*>" contains=jsm_label_delim

syntax match jsm_comment "\/\/.*$" contains=jsm_todo
syntax match jsm_comment "\/\*\_.*\*\/" contains=jsm_todo

highlight link jsm_keyword Keyword

highlight link jsm_number Number
highlight link jsm_hex Number
highlight link jsm_binary Number
highlight link jsm_address Include

highlight link jsm_ref_delim Delimiter

highlight link jsm_name Underlined
highlight link jsm_name_delim Delimiter
highlight link jsm_label Identifier
highlight link jsm_label_delim Delimiter

highlight link jsm_comment Comment
highlight link jsm_todo Todo

let &cpo = s:cpo_save
unlet s:cpo_save
