# -*- coding: utf-8 -*-
# @Time    : 2019/2/17 2:58
# @Author  : J.K LuMinzhe
# @Site    :
# @File    : ScreenShotsList.py
# @Software: PyCharm

import os
import shutil
import time
import random

from win32com.shell import shell, shellcon

def deltorecyclebin(filename):
  shell.SHFileOperation((0,shellcon.FO_DELETE,filename,None,
    shellcon.FOF_SILENT |
    shellcon.FOF_ALLOWUNDO |
    shellcon.FOF_NOCONFIRMATION,
    None,None))

def get_year(timestamp):
  timeStruct = time.localtime(timestamp)
  return str(timeStruct.tm_year)

def make_list(dirname, output_file, new_dirname):
  image_list = {}
  for dir, sub_dir, images in os.walk(dirname):
    for image in images:
      image_file = os.path.join(dir, image)
      store_key = hash(open(image_file, 'rb').read())
      if store_key in image_list:
        print('Find same images: %s, %s' % (image_list[store_key], image_file))
      else:
        image_list[store_key] = [image, dir, get_year(os.path.getmtime(image_file))]
  print(len(image_list))
  
  fout = open(output_file, 'w')
  for store_key in image_list:
    image_info = image_list[store_key]
    fout.write('\t'.join(image_info) + '\n')
  fout.close()
  # open(output_file, 'w').write('\n'.join(image_list.values()))
  
  for store_key in image_list:
    image_info = image_list[store_key]
    year = image_info[2]
    dst_path = os.path.join(new_dirname, r'趣图' + year)
    if not os.path.exists(dst_path):
      os.makedirs(dst_path)
    image = image_info[0]
    src_dir = image_info[1]

    new_image = image
    if os.path.exists(os.path.join(dst_path, image)):
      new_image = '%s_rand%04d.%s' % (image.split('.')[0], random.randint(0, 10000), image.split('.')[1])
    
    shutil.move(os.path.join(src_dir, image),
                    os.path.join(dst_path, new_image))

def remove_duplicate(target_dir, src_dir):
  image_list = {}
  for dir, sub_dir, images in os.walk(target_dir):
    for image in images:
      image_file = os.path.join(dir, image)
      store_key = hash(open(image_file, 'rb').read())
      if store_key in image_list:
        print('Find same images: %s, %s' % (image_list[store_key], image_file))
      else:
        image_list[store_key] = [image, dir, get_year(os.path.getmtime(image_file))]
  print(len(image_list))
  print('~'*80)
  print('~'*80)
  print('~'*80)
  
  for dir, sub_dir, images in os.walk(src_dir):
    for image in images:
      image_file = os.path.join(dir, image)
      store_key = hash(open(image_file, 'rb').read())
      if store_key in image_list:
        print('Find same images: %s, %s' % (image_list[store_key], image_file))
        deltorecyclebin(image_file)

def main():
  print('hello')
  # make_list(r'E:\我的电脑\07_Photo\03_趣图_old',
  #           r'C:\Users\Administrator\Desktop\photo_list.txt',
  #           r'E:\我的电脑\07_Photo\03_趣图')
  # remove_duplicate(r'E:\我的电脑\07_Photo\03_趣图',
  #                  r'F:\Photo')
  # make_list(r'F:\Photo',
  #           r'C:\Users\Administrator\Desktop\photo_list.txt',
  #           r'E:\我的电脑\07_Photo\03_趣图')
  print('welcome')


if __name__ == '__main__':
  main()
