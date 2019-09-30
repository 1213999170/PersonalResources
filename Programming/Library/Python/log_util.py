# -*- coding: utf-8 -*-
# @Time    : 2018/9/24 0024 22:11
# @Author  : J.K LuMinzhe
# @Site    : 
# @File    : log_util.py
# @Software: PyCharm

import os
import sys
import math
import time


class Watch():
  def __init__(self, info_title='WatchInfo', gap_time=1, do_print=True):
    self.info_title = info_title
    self.init_time = time.time()
    
    self.count = 0
    self.last_time = self.init_time
    self.gap_time = gap_time
    
    self.do_print = do_print
  
  def switch_print(self, context):
    if self.do_print:
      context = str(context)
      print(context)
  
  def display(self, context=''):
    cur_time = time.time()
    if 0 == self.count or cur_time >= self.last_time + self.gap_time:
      self.switch_print('[%s %.1f %4d]: %s' % (
                  self.info_title, cur_time - self.init_time, self.count, context))
      self.last_time = cur_time
    self.count += 1
  
  def show(self, context=''):
    self.switch_print('[%s %.1f]: %s' % (
                  self.info_title, time.time() - self.init_time, context))

