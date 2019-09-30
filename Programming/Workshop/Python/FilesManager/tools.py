# -*- coding: utf-8 -*-
# @Time    : 2019/2/17 15:27
# @Author  : J.K LuMinzhe
# @Site    : 
# @File    : Tools.py
# @Software: PyCharm

import os
import sys
import math
import time
import hashlib

import log_util

from win32com.shell import shell, shellcon

def deltorecyclebin(filename):
  shell.SHFileOperation((0,shellcon.FO_DELETE,filename,None,
    shellcon.FOF_SILENT |
    shellcon.FOF_ALLOWUNDO |
    shellcon.FOF_NOCONFIRMATION,
    None,None))

def get_md5(input_bytes):
  md5 = hashlib.md5()
  md5.update(input_bytes)
  return md5.hexdigest()

def get_year(timestamp):
  timeStruct = time.localtime(timestamp)
  return str(timeStruct.tm_year)

def make_list(target_dir, remove_mark = True):
  watch = log_util.Watch('MakeListInfo')
  image_list = {}
  for dir, sub_dir, images in os.walk(target_dir):
    for image in images:
      watch.display()
      image_file = os.path.join(dir, image)
      store_key = get_md5(open(image_file, 'rb').read())
      if store_key in image_list:
        print('Find same images: %s, %s' % (image_list[store_key], image_file))
        if remove_mark:
          deltorecyclebin(image_file)
      else:
        image_list[store_key] = [str(store_key), image, dir, get_year(os.path.getmtime(image_file))]
  return image_list

def write_list_to_file(image_list, list_file):
  fout = open(list_file, 'w')
  for store_key in image_list:
    image_info = image_list[store_key]
    fout.write(','.join(image_info) + '\n')
  fout.close()

def read_list_from_file(list_file):
  image_list = {}
  for line in open(list_file, 'r').read().strip('\n').split('\n'):
    image_list[int(line.split(',')[0])] = line.split(',')
  return image_list

def merge_list(image_list1, image_list2):
  for store_key in image_list2:
    if store_key not in image_list1:
      image_list1[store_key] = image_list2[store_key]
    else:
      if image_list1[store_key] != image_list2[store_key]:
        print('find same images:', image_list1[store_key], image_list2[store_key])

def remove_duplicate(image_list, target_dir):
  for dir, sub_dir, images in os.walk(target_dir):
    for image in images:
      image_file = os.path.join(dir, image)
      store_key = get_md5(open(image_file, 'rb').read())
      if store_key in image_list:
        print('Find same images: %s, %s' % (image_list[store_key], image_file))
        deltorecyclebin(image_file)
