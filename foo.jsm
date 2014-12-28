init:
  @A000 | out
  $30 | zero
  #8 | bits // bit count
  #7 | num // num to show

each_bit:
  dupe ~10000000 and
  #7 shr
  zero add
  out store
  out #1 add &out store
  #1 shl // move num to next bit
  bits #1 sub &bits store
  bits :each_bit jnz

halt
