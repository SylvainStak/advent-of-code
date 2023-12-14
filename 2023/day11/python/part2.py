#!/bin/python3

fabric = [list(_.strip()) for _ in open('../input.txt','r').readlines()]

empty_rows = []
empty_columns = []

# Scan vertically / horizontally and search empty lines
for i in range(len(fabric)):
  filled = False
  for j in range(len(fabric[0])):
    if fabric[i][j] == '#':
      filled = True
  if not filled:
    empty_rows.append(i)

for i in range(len(fabric[0])):
  filled = False
  for j in range(len(fabric)):
    if fabric[j][i] == '#':
      filled = True
  if not filled:
    empty_columns.append(i)

# Store all possible pair combinations between galaxies
m = 1000000
galaxies = []
combos = []

for x in range(len(fabric)):
  for y in range(len(fabric[0])):
    if fabric[x][y] == '#':
      offset_x = 0
      offset_y = 0

      for r_id in empty_rows:
        if r_id < x:
          offset_x += m-1

      for c_id in empty_columns:
        if c_id < y:
          offset_y += m-1

      galaxies.append((x+offset_x, y+offset_y))

for g1 in galaxies:
  for g2 in galaxies:
    if all([g1 != g2, (g1, g2) not in combos, (g2, g1) not in combos]):
      combos.append((g1, g2))


# Result is the sum of the manhattan distance between each pair
print(sum(list(map(lambda c: abs(c[0][0]-c[1][0])+abs(c[0][1]-c[1][1]), combos))))

