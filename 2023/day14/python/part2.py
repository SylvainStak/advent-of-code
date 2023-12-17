#!/bin/python3

_input = [[c for c in line.strip()] for line in open('../input.txt','r').readlines()]

for _ in range(1000000000):
  # NORTH
  for row in range(len(_input)):
    for col in range(len(_input[0])):
      if row > 0 and _input[row][col] == 'O':
        clear = False
        for i in range(row)[::-1]:
          if _input[i][col] == '#' or _input[i][col] == 'O':
            _input[row][col] = '.'
            _input[i+1][col] = 'O'
            clear = True
            break
        if not clear:
          _input[row][col] = '.'
          _input[0][col] = 'O'

  # WEST
  for row in range(len(_input)):
    for col in range(len(_input[0])):
      if col > 0 and _input[row][col] == 'O':
        clear = False
        for i in range(col)[::-1]:
          if _input[row][i] == '#' or _input[row][i] == 'O':
            _input[row][col] = '.'
            _input[row][i+1] = 'O'
            clear = True
            break
        if not clear:
          _input[row][col] = '.'
          _input[row][0] = 'O'

  # SOUTH
  for row in range(len(_input))[::-1]:
    for col in range(len(_input[0]))[::-1]:
      if row < len(_input)-1 and _input[row][col] == 'O':
        clear = False
        for i in range(row+1, len(_input)):
          if _input[i][col] == '#' or _input[i][col] == 'O':
            _input[row][col] = '.'
            _input[i-1][col] = 'O'
            clear = True
            break
        if not clear:
          _input[row][col] = '.'
          _input[len(_input)-1][col] = 'O'

  # EAST
  for row in range(len(_input))[::-1]:
    for col in range(len(_input[0]))[::-1]:
      if col < len(_input[0])-1 and _input[row][col] == 'O':
        clear = False
        for i in range(col+1, len(_input[0])):
          if _input[row][i] == '#' or _input[row][i] == 'O':
            _input[row][col] = '.'
            _input[row][i-1] = 'O'
            clear = True
            break
        if not clear:
          _input[row][col] = '.'
          _input[row][len(_input[0])-1] = 'O'


load = 0
for row in range(len(_input)):
  for col in range(len(_input[0])):
    if _input[row][col] == 'O':
      load += len(_input)-row
print(load)

