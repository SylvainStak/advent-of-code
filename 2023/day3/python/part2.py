#!/bin/python3

_input = [_.strip() for _ in open('../input.txt','r').readlines()]

def get_n_from_coords(m, x, y):
  if not m[x][y].isnumeric():
    return False
  num_str = ''
  while y > 0 and m[x][y-1].isnumeric():
    y-=1
  while y < len(m[x]) and m[x][y].isnumeric():
    num_str += m[x][y]
    y+=1
  return int(num_str)


coords = []
for row in range(len(_input)):
  for col in range(len(_input[0])):
    if _input[row][col] == '*':
      c_subset = []
      for x in range(-1, 2):
        for y in range(-1, 2):
          if _input[row+x][col+y].isnumeric():
            c_subset.append((row+x, col+y))
      coords.append(c_subset)

total = sum([_[0]*_[1] for _ in list(filter(lambda l: len(l) == 2, map(lambda subset: list(set(map(lambda c: get_n_from_coords(_input, c[0], c[1]), subset))), coords)))])

print(total)

