#!/bin/python3

_input = [_.strip() for _ in open('../input.txt','r').readlines()]

WIDTH = len(_input)
HEIGHT = len(_input[0])
total = 0

for row in range(WIDTH):
  num_str = ''
  is_valid = False

  for col in range(HEIGHT):
    digit = _input[row][col]

    if not digit.isnumeric():
      if is_valid:
        total += int(num_str)
        is_valid = False
      num_str = ''
      continue

    num_str += digit

    if not is_valid:
      for x in range(-1, 2):
        for y in range(-1, 2):
          if 0 <= row+x < WIDTH and 0 <= col+y < HEIGHT:
            cell = _input[row+x][col+y]
            if not cell.isnumeric() and cell != '.':
              is_valid = True

  if num_str and is_valid:
    total += int(num_str)

print(total)

