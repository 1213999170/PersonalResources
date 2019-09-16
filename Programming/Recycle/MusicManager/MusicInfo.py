# -*- coding: utf-8 -*-
# @Time    : 2019/3/31 13:22
# @Author  : J.K LuMinzhe
# @Site    : 
# @File    : MucisInfo.py
# @Software: PyCharm

import os
import sys
import math
import time
import json
import collections

class MusicInfo:
  def __init__(self, music=None):
    if not music:
      self.get_default()
    else:
      self.name      = music['name']
      self.singers   = music['singers']
      self.language  = music['language']
      self.file      = music['file']
      self.tags      = music['tags']
      self.md5       = music['md5']
      self.favor     = music['favor']
  
  def get_default(self):
    self.name     = r''
    self.singers  = set()
    self.language = 0
    self.file     = r''
    self.tags     = set()
    self.md5      = 0
    self.favor    = r''
  
  def get_dict(self):
    d = collections.OrderedDict()
    d['name']     = self.name
    d['singers']  = self.singers
    d['language'] = self.language
    d['file']     = self.file
    d['tags']     = self.tags
    d['md5']      = self.md5
    d['favor']    = self.favor
    return d
