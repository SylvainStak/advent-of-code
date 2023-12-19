#!/bin/python3

_input = sorted([int(_.strip()) for _ in open('../input.txt','r').readlines()])

diff1 = 1
diff3 = 1

for i in range(len(_input)-1):
  diff = _input[i+1]-_input[i]
  diff1 += diff == 1
  diff3 += diff == 3

print(diff1*diff3)

