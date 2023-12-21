#!/bin/python3

import sys
_input = [_.strip() for _ in open('../input.txt','r').readlines()]

target = int(_input[0])
ids = [int(b) for b in _input[1].split(',') if b != 'x']
t = sys.maxsize
t_id = 0

for bus in ids:
  next_t = bus*(target//bus+1)
  if next_t < t:
    t = next_t
    t_id = bus

print((t-target)*t_id)

