#!/bin/python3

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

steps = 0
next_id = 'AAA'

while next_id != 'ZZZ':
  inst = instructions[steps%len(instructions)]
  next_id = network[next_id][inst]
  steps += 1

print(steps)

