print_byte_binary: // num 
  |@A000 => out
  |$30 => zero
  |#8 => bits

  out bits #2 ref load // num out bits num
  each_bit:
    ~10000000 and // num out bits mask
    #7 shr // num out bits mask
    zero add // num out bits ascii
    #2 ref load store // num out bits
    #1 ref load #1 add #2 ref store // num out bits
    #2 ref load #1 shl #3 ref store // num out bits
    #1 sub // num out bits
    #2 ref load // num out bits num
    #1 ref load :each_bit jnz // num out bits num

halt
