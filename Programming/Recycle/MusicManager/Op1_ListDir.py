# -*- coding: utf-8 -*-
# @Time    : 2019/4/28 1:48
# @Author  : J.K LuMinzhe
# @Site    : 
# @File    : Op1_ListDir.py
# @Software: PyCharm

import os
import sys
import math
import time

import io_util

import Head


def ListDir(dir, output_file):
  fout = open(output_file, 'w')
  for cur_path, sub_dir, files in os.walk(dir):
    for file in files:
      file.encode(encoding='gbk')
      path_filename = os.path.join(cur_path, file)
      if Head.JudgeMusicFile(path_filename):
        fout.write(io_util.get_md5(path_filename))
        fout.write('\t' + path_filename + '\t' + file + '\n')
  fout.close()


def main():
  print('hello')
  ListDir(r'F:\Music\new downloads', r'F:\Music\cur_music_list.txt')
  print('welcome')


if __name__ == '__main__':
  main()
