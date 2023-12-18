#!/bin/python3

_input = [_.strip().replace(', ', ',').replace(' contain ', ':').replace(' bags', '').replace(' bag', '').replace('.', '') for _ in open('../input.txt','r').readlines()]
rules = {rule.split(':')[0]: list(filter(lambda f: f[1] != ' other', map(lambda b: (int(b[0]) if b[0].isnumeric() else b[0], b[2:]), rule.split(':')[1].split(',')))) for rule in _input}
count_bags = lambda bag: sum([in_bag[0]*count_bags(in_bag[1]) for in_bag in rules.get(bag)])+1

print(count_bags('shiny gold')-1)

