# -*- coding: utf-8 -*-
# @Time    : 2019/4/6 16:27
# @Author  : J.K LuMinzhe
# @Site    : 
# @File    : functions.py
# @Software: PyCharm

import os
import sys
import math
import time
from xpinyin import Pinyin

def add_to_dict(base, key, value, checkRepeat=False):
  # checkRepeat:
  #   True : will check the repeat key before adding key-value to dictionary 'base'
  if (key not in base.keys()) or (not checkRepeat):
    base[key] = value
  else:
    raise RuntimeError('Find repeated key', key, ', please check the code')


def get_first_letter(name, num = 1):
  p = Pinyin()
  character_name = p.get_pinyin(name, '').lower()
  
  if num == 1:
    return character_name[0]
  if len(character_name) < num:
    character_name += '0' * (num - len(character_name))
  return character_name[0:num]

def split_command_line(command_line):
  word = ''
  words = []
  brace_stack = []
  for c in command_line:
    if c != ' ':
      if brace_stack and c == brace_stack[-1]:
        brace_stack.pop(-1)
      elif c == '"' or c == "'":
        brace_stack.append(c)
      else:
        word += c
    else:
      if not brace_stack:
        words.append(word)
        word = ''
      else:
        word += c
  if word:
    words.append(word)
  
  if brace_stack:
    return ['invalid_command']
  return words