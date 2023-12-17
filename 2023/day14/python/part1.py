#!/bin/python3

_input = [_.strip() for _ in open('../input.txt','r').readlines()]
total = 0

for row in range(len(_input)):
  for col in range(len(_input[0])):
    if _input[row][col] == 'O':
      rocks = 0
      ref = row
      for i in range(row)[::-1]:
        ref = i
        if _input[i][col] == '#':
          ref += 1
          break
        if _input[i][col] == 'O':
          rocks += 1
      x = len(_input)-ref-rocks
      total += x

print(total)

