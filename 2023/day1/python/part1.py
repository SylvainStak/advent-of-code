#!/bin/python3

_input = [_.strip() for _ in open('../input.txt','r').readlines()]

total = 0
digits = []

for line in _input:
    for char in line:
        if char.isnumeric():
            digits.append(char)
    total += int(f'{digits[0]}{digits[-1]}')
    digits.clear()

print(total)

