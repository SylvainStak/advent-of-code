#!/bin/python3

_input = [_.strip() for _ in open('../input.txt','r').readlines()]

def trace(v_list):
  if all(v == 0 for v in v_list[-1]): 
    return v_list
    
  lt = v_list[-1]
  return trace(v_list+[[lt[i+1]-lt[i] for i in range(len(lt)-1)]])


total = 0
for hl in _input:
  history = list(map(int, hl.split(' ')))
  total += sum(t[-1] for t in trace([history]))

print(total)

