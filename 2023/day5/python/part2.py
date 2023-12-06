#!/bin/python3

_input = [_.strip() for _ in open('../input.txt','r').readlines()]
seeds = list(map(int, _input[0].split(':')[1].strip().split(' '))) 
_input = _input[2:]+['']

maps = []
m_buffer = []

for line in _input:
  if line and 'map' not in line:
    m_buffer.append(list(map(int, line.split(' '))))
  else:
    maps.append(m_buffer)
    m_buffer = []

maps = list(filter(lambda _: len(_), maps))
import sys
location = sys.maxsize

for pair_id in range(0, len(seeds), 2):
  for seed in range(seeds[pair_id], seeds[pair_id]+seeds[pair_id+1]):
    num = seed
    for map_set in maps:
      is_mapped = False
      for map_subset in map_set:
        if map_subset[1] <= num < map_subset[1] + map_subset[2]:
          num = num - map_subset[1] + map_subset[0] if not is_mapped else num
          is_mapped = True  

    location = num if num < location else location

print(location)

