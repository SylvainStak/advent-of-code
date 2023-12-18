#!/bin/python3

_input = [_.strip() for _ in open('../input.txt','r').readlines()]

def next_beams(prev_beam):
  new_beams = []
  next_dir = {
    '.': {'l':'l', 'r':'r', 'u':'u', 'd':'d'},
    '-': {'l':'l', 'r':'r', 'u':'lr', 'd':'lr'},
    '|': {'l':'ud', 'r':'ud', 'u':'u', 'd':'d'},
    '/': {'l':'d', 'r':'u', 'u':'r', 'd':'l'},
    '\\': {'l':'u', 'r':'d', 'u':'l', 'd':'r'},
  }.get(_input[prev_beam['x']][prev_beam['y']], {}).get(prev_beam['dir'])

  for d in next_dir:
    next_beam = {'x': prev_beam['x'], 'y': prev_beam['y'], 'dir': d}
    speed = {'l':(0, -1), 'r':(0, 1), 'u':(-1, 0), 'd':(1, 0)}.get(d)
    next_beam['x'] += speed[0]
    next_beam['y'] += speed[1]

    if all([
      0 <= next_beam['x'] < len(_input),
      0 <= next_beam['y'] < len(_input[0])
    ]):
      new_beams.append(next_beam)

  return new_beams 


def get_energized(starting_beam):
  energized = []
  momentums = []
  beams_buffer = []
  beams = [starting_beam]

  while len(beams):
    for beam in beams:
      tile = tuple(beam.values())
      if tile not in momentums: 
        momentums.append(tile)

      tile = tile[:-1]
      if tile not in energized: 
        energized.append(tile)

      for new_pos in next_beams(beam):
        beams_buffer.append(new_pos)
    
    beams = []
    for beam in beams_buffer:
      if tuple(beam.values()) not in momentums: 
        beams.append(beam)
    beams_buffer = []

  return len(energized)


starting_beams = [
  *[{'x': 0, 'y': _, 'dir': 'd'} for _ in range(len(_input[0]))],
  *[{'x': len(_input)-1, 'y': _, 'dir': 'u'} for _ in range(len(_input[0]))],
  *[{'x': _, 'y': 0, 'dir': 'r'} for _ in range(len(_input))],
  *[{'x': _, 'y': len(_input[0])-1, 'dir': 'l'} for _ in range(len(_input))],
]

print(max([get_energized(beam) for beam in starting_beams]))

