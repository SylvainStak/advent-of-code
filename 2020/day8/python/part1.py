#!/bin/python3

_input = [_.strip() for _ in open('../input.txt','r').readlines()]
code = [(inst.split(' ')[0], int(inst.split(' ')[1])) for inst in _input]
cache = []
ptr = 0
acc = 0

while(ptr not in cache):
  cache.append(ptr)
  op = code[ptr][0]
  arg = code[ptr][1]

  if op == 'acc':
    acc += arg
  elif op == 'jmp':
    ptr += arg-1

  ptr += 1

print(acc)

