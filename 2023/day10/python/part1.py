#!/bin/python3

p_matrix = [_.strip() for _ in open('../input.txt','r').readlines()]

# Find coords from S
for x in range(len(p_matrix)):
  for y in range(len(p_matrix[0])):
    if p_matrix[x][y] == 'S':
      s_x = x
      s_y = y
      break

s_pipes = [
  ('-LF', 'e',  0, -1),
  ('-J7', 'w',  0,  1),
  ('|7F', 's', -1,  0),
  ('|JL', 'n',  1,  0),
]

# Find a pipe connected to S so loop can be started from there
for p in s_pipes:
  c_pipe = p_matrix[s_x+p[2]][s_y+p[3]]
  if c_pipe in p[0]:
    p_dir = p[1]
    s_x += p[2]
    s_y += p[3]
    break


dirs = {
  '|': {'n':'s','s':'n'},
  '-': {'w':'e','e':'w'},
  'L': {'n':'e','e':'n'},
  'J': {'n':'w','w':'n'},
  '7': {'w':'s','s':'w'},
  'F': {'e':'s','s':'e'},
}

# Start following the pipe directions until getting back to S
steps = 1
while c_pipe != 'S':
  n_dir = dirs.get(c_pipe).get(p_dir)

  if n_dir in 'ns':
    s_x += 1 if n_dir == 's' else -1
  elif n_dir in 'we':
    s_y += 1 if n_dir == 'e' else -1

  c_pipe = p_matrix[s_x][s_y]
  p_dir = {'n':'s', 's':'n', 'w':'e', 'e':'w'}.get(n_dir)
  steps+=1

print(steps/2)

