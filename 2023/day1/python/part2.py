#!/bin/python3

_input = [_.strip() for _ in open('../input.txt','r').readlines()]

total = 0
digits = []
valid_digits = ['1','2','3','4','5','6','7','8','9','one','two','three','four','five','six','seven','eight','nine']

for line in _input:
    while len(line):
        d_found = False
        d_found_index = 0
        while not d_found and d_found_index < len(valid_digits):
            vd = valid_digits[d_found_index]
            if line.startswith(vd):
                digits.append(valid_digits[d_found_index-9] if len(vd) > 1 else vd)
                d_found = True
            d_found_index += 1
        line = line[1:]
    total += int(f'{digits[0]}{digits[-1]}')
    digits.clear()

print(total)

