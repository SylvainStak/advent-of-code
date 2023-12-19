#!/bin/python3

_input = [int(_.strip()) for _ in open('../input.txt','r').readlines()]
preamble_length = 25

def is_valid(num, preamble):
  for i in preamble:
    for j in preamble:
      if i != j and i+j == num:
        return True
  return False

def get_invalid_num():
  for i in range(preamble_length, len(_input)):
    num = _input[i]
    preamble = _input[i-preamble_length:i]
    if not is_valid(num, preamble):
      return num


target = get_invalid_num()

for w_len in range(2, len(_input)+1):
  for i in range(len(_input)-w_len+1):
    window = _input[i:i+w_len]
    if sum(window) == target:
      print(min(window)+max(window))

