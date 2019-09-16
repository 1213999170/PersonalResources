# -*- coding: utf-8 -*-
# @Time    : 2019/2/17 15:43
# @Author  : J.K LuMinzhe
# @Site    : 
# @File    : main.py
# @Software: PyCharm

import os
import sys
import math
import time

import tools
import random
import shutil

def move_images(image_list, dst_dir):
  for store_key in image_list:
    image_info = image_list[store_key]
    year = image_info[3]
    dst_path = os.path.join(dst_dir, r'趣图' + year)
    if not os.path.exists(dst_path):
      os.makedirs(dst_path)
    image = image_info[1]
    src_dir = image_info[2]
    
    new_image = image
    if os.path.exists(os.path.join(dst_path, image)):
      new_image = '%s_rand%04d.%s' % (image.split('.')[0], random.randint(0, 10000), image.split('.')[1])
    
    shutil.move(os.path.join(src_dir, image),
                os.path.join(dst_path, new_image))


def main():
  print('hello')
  # image_list = tools.make_list(r'E:\我的电脑\07_Photo\02_Photo')
  # tools.remove_duplicate(image_list, r'E:\我的电脑\07_Photo\手机资料20180903\照片'))
  # image_list = tools.make_list(r'E:\我的电脑\07_Photo\02_Photo')
  # tools.remove_duplicate(image_list, r'F:\Temp')
  
  image_list = tools.make_list(r'F:\Temp')
  move_images(image_list, r'E:\我的电脑\07_Photo\03_趣图')
  
  print('welcome')


if __name__ == '__main__':
  main()
