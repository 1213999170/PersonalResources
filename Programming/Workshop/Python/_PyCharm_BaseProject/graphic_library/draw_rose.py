# -*- coding: utf-8 -*-
# @Time    : 2019/2/17 19:40
# @Author  : J.K LuMinzhe
# @Site    : 
# @File    : draw_rose.py
# @Software: PyCharm

import os
import sys
import math
import time

import matplotlib.pyplot as plt

plt.rcdefaults()

import matplotlib.pyplot as plt
import matplotlib.patches as mpatches


def add_sector(radius, baseline, label, start_angle, degrees):
  if baseline:
    base_wedge = mpatches.Wedge((0, 0), baseline, start_angle, degrees, facecolor='grey', edgecolor='grey')
  else:
    base_wedge = None
  wedge = mpatches.Wedge((0, 0), radius, start_angle, degrees, facecolor='green', edgecolor='red')
  return wedge, base_wedge


def draw_nightingale_rose(label, data, baseline=None):
  fig, ax = plt.subplots()
  
  num = len(data)
  delta_degree = 360 / num;
  epsilon = 0.25
  
  for i in range(num):
    start_angle = delta_degree * i + epsilon
    end_degrees = start_angle + delta_degree - 2 * epsilon
    radius = data[i]
    wedge, base_wedge = add_sector(radius, baseline, None, start_angle, end_degrees)
    if base_wedge:
      ax.add_patch(base_wedge)
    ax.add_patch(wedge)
  
  plt.axis('equal')
  plt.axis('off')
  plt.show()




def main():
  print('hello')
  lines = open('data.txt', 'r').read().strip('\n').split('\n')
  dates = []
  scores = []
  for line in open('data.txt', 'r').read().strip('\n').split('\n'):
    date, score = line.split('\t')
    dates.append(date)
    scores.append(int(score))
  
  draw_nightingale_rose(dates, scores, 6)
  print('welcome')


if __name__ == '__main__':
  main()
