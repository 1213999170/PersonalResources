# -*- coding: utf-8 -*-
# @Time    : 2019/3/2 22:26
# @Author  : J.K LuMinzhe
# @Site    : 
# @File    : test.py
# @Software: PyCharm

import os
import sys
import math
import time

def duplicate_rows(rows, number):
  length = len(rows)
  degs = number // length
  left_number = number - degs * length
  print(number, length, degs, left_number)
  
  blank_row = ['', '0']
  output_rows = []
  for i in range(length):
    if i < left_number:
      for j in range(degs):
        if j != degs//2:
          output_rows.append(['', rows[i][1]])
        else:
          output_rows.append(rows[i])
    else:
      for j in range(degs - 1):
        if j != degs//2:
          output_rows.append(['', rows[i][1]])
        else:
          output_rows.append(rows[i])
    output_rows.append(blank_row)
  return output_rows


def test(data_file, output_file):
  lines = open(data_file, 'r').read().strip('\n').split('\n')
  rows = [line.split('\t') for line in lines]
  print(rows)
  
  output_rows = duplicate_rows(rows, 360)
  
  output = open(output_file, 'w')
  for row in output_rows:
    line = '\t'.join(row)
    output.write(line + '\n')
  output.close()


def main():
  print('hello')
  test(r'data.txt', r'output_data.txt')
  print('welcome')


if __name__ == '__main__':
  main()
