#!/bin/python3

from functools import cmp_to_key

_input = [_.strip() for _ in open('../input.txt','r').readlines()]
hands = [[] for _ in range(7)]

# Separate by groups
for line in _input:
  l = line.split(' ')
  h_cache = {}
  for card in l[0]:
    h_cache[card] = h_cache.get(card, 0) + 1

  combo = {1: 0, 2: 0, 3: 0, 4: 0, 5: 0}
  for v in h_cache.values():
      combo[v] += 1

  r = 0 # High Card (default)
  if combo[5]: r = 6 # Five of a kind
  elif combo[4]: r = 5 # Quads
  elif combo[3]==1 and combo[2]==1: r = 4 # Full House
  elif combo[3]==1 and combo[1]==2: r = 3 # Trips
  elif combo[2]==2: r = 2 # Double Pair
  elif combo[2]==1: r = 1 # Pair

  hands[r].append({'hand': l[0], 'bid': int(l[1])})

def compare_hands(h1, h2):
  cv = lambda c: '23456789TJQKA'.index(c)
  for c in range(5):
    v1 = cv(h1['hand'][c])
    v2 = cv(h2['hand'][c])
    if v1 != v2:
      return v1-v2

# Sort inner groups and flatten into a 1D list
hands = [hand for group in list(map(lambda group: sorted(group, key=cmp_to_key(compare_hands)), hands)) for hand in group]
print(sum([hands[h]['bid']*(h+1) for h in range(len(hands))]))

