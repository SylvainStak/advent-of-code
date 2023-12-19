#!/bin/python3

_input = [list(_.strip()) for _ in open('../input.txt','r').readlines()]

def get_next_gen(prev_gen):
  next_gen = [_[:] for _ in prev_gen]

  for i in range(len(prev_gen)):
    for j in range(len(prev_gen[0])):
      if prev_gen[i][j] == '.':
        continue
      
      neighbors = 0
      for x in range(-1, 2):
        for y in range(-1, 2):
          _x = i+x
          _y = j+y

          if all([
            0 <= _x < len(prev_gen),
            0 <= _y < len(prev_gen[0]),
            not (_x == i and _y == j),
          ]):
            if prev_gen[_x][_y] == '#':
              neighbors += 1
      
      if prev_gen[i][j] == 'L' and neighbors == 0:
        next_gen[i][j] = '#'
      elif prev_gen[i][j] == '#' and neighbors > 3:
        next_gen[i][j] = 'L'

  return next_gen
          

last_gen = []
curr_gen = _input
while (last_gen != curr_gen):
  last_gen = curr_gen
  curr_gen = get_next_gen(curr_gen)

print(len(list(filter(lambda s: s=='#', ''.join([''.join(i) for i in curr_gen])))))

