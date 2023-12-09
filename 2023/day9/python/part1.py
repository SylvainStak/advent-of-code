#!/bin/python3

_input = [_.strip() for _ in open('../input.txt','r').readlines()]
total = 0

for _ in _input:
  trace = [list(map(int, _.split(' ')))]
  while not all([t == 0 for t in trace[-1]]):
    lt = trace[-1]
    nt = [lt[i+1]-lt[i] for i in range(len(lt)-1)]
    trace.append(nt)
  total += sum([t[-1] for t in trace])

print(total)

