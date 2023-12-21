#!/bin/python3

_input = [_.strip() for _ in open('../input.txt','r').readlines()]
ids = [(k, int(v)) for k, v in enumerate(_input[1].split(',')) if v != 'x']

i = 0
while True:
  i += 1
  is_valid = True
  for _id in ids:
    if (i+_id[0])%_id[1] != 0:
      is_valid = False
  if is_valid:
    print(i)
    break

