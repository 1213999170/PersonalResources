# -*- coding: utf-8 -*-
# @Time    : 2018/10/21 0021 00:29
# @Author  : J.K LuMinzhe
# @Site    : 
# @File    : cc.py
# @Software: PyCharm

import os
import sys
import math
import time

import requests
import json

def main():
  dir = r'F:\Music'
  fout = r'C:\Users\Administrator\Downloads\music.txt'
  music = []
  for dir, subdir, files in os.walk(dir):
    for file in files:
      music.append(file)
  
  print(len(music), music[0])
  open(fout, 'w', encoding='utf-8').write('\n'.join(music))


if __name__ == '__main__':
  main()
