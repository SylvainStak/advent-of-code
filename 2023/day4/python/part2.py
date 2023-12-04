#!/bin/python3

_input = [_.strip() for _ in open('../input.txt','r').readlines()]

cards = []

for line in _input:
  line_splitted = line.split('|')
  w_numbers = list(filter(lambda _: _ != '', line_splitted[0].split(':')[1].split(' ')))
  s_numbers = list(filter(lambda _: _ != '', line_splitted[1].split(' ')))
  valid = sum([1 for _ in s_numbers if _ in w_numbers])
  cards.append({'valid': valid, 'instances': 1})

for c in range(len(cards)):
  for _ in range(cards[c]['instances']):
    c_id = 0
    while c_id < cards[c]['valid']:
      cards[c_id+c+1]['instances'] += 1
      c_id += 1

print(sum(list(map(lambda _: _['instances'], cards))))

