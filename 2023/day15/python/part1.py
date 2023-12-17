#!/bin/python3

init_sequence = open('../input.txt','r').readlines()[0].strip().split(',')
total = 0

for step in init_sequence:
  value = 0
  for c in step:
    value = (value+ord(c))*17%256
  total += value

print(total)

