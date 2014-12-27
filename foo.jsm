init:
  out => @A000
  zero => $30
  bits => #8 // bit count
  num => #4 // num to show

each_bit:
  dupe ~10000000 and
  #7 shr
  zero add
  out store
  out #1 add &out store
  #1 shl // move num to next bit
  bits #1 sub &bits store
  :each_bit jnz

halt
