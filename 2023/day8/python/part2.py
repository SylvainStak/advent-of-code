#!/bin/python3

from math import lcm

_input = [_.strip() for _ in open('../input.txt','r').readlines()]
instructions = _input[0]
_input = _input[2:]

network = {}

for node in _input:
  splitted = node.replace('(', '').replace(')', '').replace(' ', '').split('=')
  n_id = splitted[0]
  n_left = splitted[1].split(',')[0]
  n_right = splitted[1].split(',')[1]
  network[n_id] = {'L': n_left, 'R': n_right}

g_steps = []
s_nodes = [k for k in network.keys() if k[-1] == 'A']
for n in range(len(s_nodes)):
  next_id = s_nodes[n]
  steps = 0
  while next_id[-1] != 'Z':    
    inst = instructions[steps%len(instructions)]
    next_id = network[next_id][inst]
    steps += 1
  g_steps.append(steps)

print(lcm(*g_steps))

