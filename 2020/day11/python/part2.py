#!/bin/python3

_input = [list(_.strip()) for _ in open('../input.txt','r').readlines()]
dirs = [(x, y) for x in range(-1, 2) for y in range(-1, 2) if x != 0 or y != 0]

def get_next_gen(prev_gen):
  next_gen = [_[:] for _ in prev_gen]

  for i in range(len(prev_gen)):
    for j in range(len(prev_gen[0])):
      if prev_gen[i][j] == '.':
        continue
      
      neighbors = 0
      for d in dirs:
        finished = False
        x = i+d[0]
        y = j+d[1]
        while all([
          0 <= x < len(prev_gen),
          0 <= y < len(prev_gen[0]),
          not finished,
        ]):
          if prev_gen[x][y] == '#':
            neighbors += 1
            finished = True
          elif prev_gen[x][y] == 'L':
            finished = True
          x += d[0]
          y += d[1]

      if prev_gen[i][j] == 'L' and neighbors == 0:
        next_gen[i][j] = '#'
      elif prev_gen[i][j] == '#' and neighbors > 4:
        next_gen[i][j] = 'L'

  return next_gen


last_gen = []
curr_gen = _input
while (last_gen != curr_gen):
  last_gen = curr_gen
  curr_gen = get_next_gen(curr_gen)

print(len(list(filter(lambda s: s=='#', ''.join([''.join(i) for i in curr_gen])))))

