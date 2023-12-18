#!/bin/python3

_input = [_.strip().replace(', ', ',').replace(' contain ', ':').replace(' bags', '').replace(' bag', '').replace('.', '') for _ in open('../input.txt','r').readlines()]
rules = {rule.split(':')[0]: list(filter(lambda f: f != ' other', map(lambda b: b[2:], rule.split(':')[1].split(',')))) for rule in _input}

def has_shiny(bag):
  inner_bags = rules.get(bag)
  for in_bag in inner_bags:
    if in_bag == 'shiny gold' or has_shiny(in_bag):
      return True
  return False

print(sum([1 for bag in rules.keys() if has_shiny(bag)]))

