#!/bin/python3

_input = [_.strip() for _ in open('../input.txt','r').readlines()]

total = 0

for line in _input:
  line_splitted = line.split('|')
  w_numbers = list(filter(lambda _: _ != '', line_splitted[0].split(':')[1].split(' ')))
  s_numbers = list(filter(lambda _: _ != '', line_splitted[1].split(' ')))
  valid = sum([1 for _ in s_numbers if _ in w_numbers])
  total += 2**(valid-1) if valid > 1 else valid

print(total)

