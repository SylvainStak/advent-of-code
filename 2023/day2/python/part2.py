#!/bin/python3

import re
import math

_input = [_.strip() for _ in open('../input.txt','r').readlines()]

prods = []
red_pattern = re.compile(r'(\d+)\sred')
green_pattern = re.compile(r'(\d+)\sgreen')
blue_pattern = re.compile(r'(\d+)\sblue')

for game in _input:
    max_red = max(list(map(int, red_pattern.findall(game))))
    max_green = max(list(map(int, green_pattern.findall(game))))
    max_blue = max(list(map(int, blue_pattern.findall(game))))

    prods.append(math.prod([max_red, max_green, max_blue]))

print(sum(prods))

