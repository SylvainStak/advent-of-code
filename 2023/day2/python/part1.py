#!/bin/python3

import re

_input = [_.strip() for _ in open('../input.txt','r').readlines()]

game_ids_sum = 0
game_id_pattern = re.compile(r'Game\s(\d+)')
red_pattern = re.compile(r'(\d+)\sred')
green_pattern = re.compile(r'(\d+)\sgreen')
blue_pattern = re.compile(r'(\d+)\sblue')

for game in _input:
    max_red = max(list(map(int, red_pattern.findall(game))))
    max_green = max(list(map(int, green_pattern.findall(game))))
    max_blue = max(list(map(int, blue_pattern.findall(game))))

    game_ids_sum += int(game_id_pattern.findall(game)[0]) if max_red <= 12 and max_green <= 13 and max_blue <= 14 else 0

print(game_ids_sum)

