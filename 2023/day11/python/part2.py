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

m = 1000000

# Expand empty lines in both directions
offset = 0
for i in empty_rows:
  for _ in range(m-1):
    fabric.insert(i+1+offset, ['.' for f in range(len(fabric[0]))])
  offset+=m-1

offset = 0
for i in empty_columns:
  for j in range(len(fabric)):
    for _ in range(m-1):
      fabric[j].insert(i+1+offset, '.')
  offset+=m-1

# Store all possible pair combinations between galaxies
galaxies = []
combos = []

for x in range(len(fabric)):
  for y in range(len(fabric[0])):
    if fabric[x][y] == '#':
      galaxies.append((x, y))

for g1 in galaxies:
  for g2 in galaxies:
    if all([g1 != g2, (g1, g2) not in combos, (g2, g1) not in combos]):
      combos.append((g1, g2))


# Result is the sum of the manhattan distance between each pair
print(sum(list(map(lambda c: abs(c[0][0]-c[1][0])+abs(c[0][1]-c[1][1]), combos))))

