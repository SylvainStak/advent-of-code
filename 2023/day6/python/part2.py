#!/bin/python3

_input = [_.strip() for _ in open('../input.txt','r').readlines()]
t = int(_input[0].split(':')[1].replace(' ', ''))
d = int(_input[1].split(':')[1].replace(' ', ''))

ways_to_win = sum([1 for i in range(t) if i*(t-i) > d])
print(ways_to_win)

