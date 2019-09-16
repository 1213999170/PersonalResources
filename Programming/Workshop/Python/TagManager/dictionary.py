# -*- coding: utf-8 -*-
# @Time    : 2019/8/4 15:05
# @Author  : J.K LuMinzhe
# @Site    : 
# @File    : dictionary.py
# @Software: PyCharm

import os
import sys
import math
import time
import collections

# words 里面保存了所有类型的单词，指定type之后，返回所有这一类单词的列表 （指定是否包含 alias）
def get_words_by_type(words, alias, type, include_alias = False):
  ret = []
  for word in words:
    if words[word] == type:
      ret.append(word)
  
  if include_alias:
    for word in alias:
      if alias[word] in ret:
        ret.append(word)
  return ret


def build_tagged_dict(tag_config):
  file = collections.OrderedDict()
  file['md5'] = ''
  file['file'] = ''
  file['name'] = ''
  for key in tag_config:
    if tag_config[key] == 'item':
      file[key] = ''
    else:
      file[key] = []
  return file

