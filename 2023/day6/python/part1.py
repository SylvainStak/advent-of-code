#!/bin/python3

_input = [_.strip() for _ in open('../input.txt','r').readlines()]
t = list(map(int, filter(lambda _: _, _input[0].split(':')[1].strip().split(' '))))
d = list(map(int, filter(lambda _: _, _input[1].split(':')[1].strip().split(' '))))
m = 1

for r in zip(t, d):
  w = 1
  for i in range(r[0]):
    if i*(r[0]-i) > r[1]:
      w += 1
  m *= w-1

print(m)

