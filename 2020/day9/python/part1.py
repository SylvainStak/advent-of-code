#!/bin/python3

_input = [int(_.strip()) for _ in open('../input.txt','r').readlines()]
preamble_length = 25

def is_valid(num, preamble):
  for i in preamble:
    for j in preamble:
      if i != j and i+j == num:
        return True
  return False

for i in range(preamble_length, len(_input)):
  num = _input[i]
  preamble = _input[i-preamble_length:i]
  if not is_valid(num, preamble):
    print(num)

