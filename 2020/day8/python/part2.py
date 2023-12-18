#!/bin/python3

_input = [_.strip() for _ in open('../input.txt','r').readlines()]
code = [[inst.split(' ')[0], int(inst.split(' ')[1])] for inst in _input]

for i in range(len(code)):
  cache = []
  finished = False
  ptr = 0
  acc = 0

  if i > 0 and code[i-1][0] == 'nop': code[i-1][0] = 'jmp'
  elif i > 0 and code[i-1][0] == 'jmp': code[i-1][0] = 'nop'
  
  if code[i][0] == 'nop': code[i][0] = 'jmp'
  elif code[i][0] == 'jmp': code[i][0] = 'nop'
  else: continue

  while(ptr not in cache and not finished):
    cache.append(ptr)
    op = code[ptr][0]
    arg = code[ptr][1]
    acc += arg if op == 'acc' else 0
    ptr += arg-1 if op == 'jmp' else 0
    ptr += 1
    finished = ptr >= len(code)

  if finished:
    print(acc)

