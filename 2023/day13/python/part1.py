#!/bin/python3

_input = [_.strip() for _ in open('../input.txt','r').readlines()]

def find_mirror(buffer):
  m_line = 0
  for i in range(len(buffer)):
    p_top = m_line
    p_bottom = m_line+1
    found = False
    while p_top > -1 and p_bottom < len(buffer) and buffer[p_top] == buffer[p_bottom]:
      p_top -= 1
      p_bottom += 1
      found = True
    m_line += 1
    if found and (p_top == -1 or p_bottom == len(buffer)):
      return m_line


rotated = lambda buff: [[row[i] for row in buff[::-1]] for i in range(len(buff[0]))]
buffer = []
v_count = 0
h_count = 0

for line in _input:
  if line != '':
    buffer.append(line)
    continue
  hor_scan = find_mirror(buffer)
  if hor_scan: h_count += hor_scan
  else: v_count += find_mirror(rotated(buffer))
  buffer = []

print(v_count+100*h_count)

