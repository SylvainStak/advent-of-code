#!/bin/python3

init_sequence = open('../input.txt','r').readlines()[0].strip().split(',')
boxes = [[] for _ in range(256)]

def get_box_id(label):
  _id = 0
  for c in label:
    _id = (_id+ord(c))*17%256
  return _id

def get_queue_id(box, label):
  for q_id in range(len(box)):
    if box[q_id]['label'] == label:
      return q_id
  return -1


for step in init_sequence:
  if '-' in step:
    step_label = step[:-1]
    box_id = get_box_id(step_label)
    queue_id = get_queue_id(boxes[box_id], step_label)
    if queue_id >= 0:
      boxes[box_id].pop(queue_id)
  else:
    step_label = step.split('=')[0]
    step_lens = step.split('=')[1]
    box_id = get_box_id(step_label)
    queue_id = get_queue_id(boxes[box_id], step_label)
    if queue_id < 0:
      boxes[box_id].append({'label': step_label, 'focal': step_lens})
    else:
      boxes[box_id][queue_id]['focal'] = step_lens

total = 0
for b_id in range(len(boxes)):
  for l_id in range(len(boxes[b_id])):
    total += (b_id+1)*(l_id+1)*int(boxes[b_id][l_id]['focal'])

print(total)

