# -*- coding: utf-8 -*-
# @Time    : 2019/3/31 13:22
# @Author  : J.K LuMinzhe
# @Site    :
# @File    : main.py
# @Software: PyCharm

import os
import sys
import math
import time

import io_util

from Manager import *


def main():
  music_root = r'F:\Music'
  music_config_file = os.path.join(music_root, r'music_config.json')
  music_list_file = os.path.join(music_root, r'music_list.json')
  music_info_file = os.path.join(music_root, r'music_info.txt')
  music_add_file = os.path.join(music_root, r'music_add.txt')
  
  # Backup
  time_pattern = time.strftime('%Y%m%d_%H%M%S', time.localtime())
  bak_config_file = os.path.join(music_root, r'Backup', r'music_config.json.bak_' + time_pattern)
  bak_list_file = os.path.join(music_root, r'Backup', r'music_list.json.bak_' + time_pattern)
  shutil.copy(music_config_file, bak_config_file)
  shutil.copy(music_list_file, bak_list_file)
  
  # Preprocess
  words, alias = InitConfiguration(music_config_file)
  music_list = GetMusicList(music_list_file)
  
  Extensions = classify_words(words)
  
  # MainProcess
  while True:
    command_line = input('$ ')
    
    command = command_line.split()[0]
    
    if command == 'q' or command == 'quit' or command == 'exit':
      break
    elif command == 'add':
      add_music(music_list, music_add_file, music_root, words, alias)
    elif len(command_line.split()) < 2:
      print('Invalid command')
    elif command == 'find':
      dir = command_line.split()[1]
      search_result = []
      invalid_search_result = []
      for curdir, subdirs, files in os.walk(dir):
        for file in files:
          if io_util.get_extension(file) in Extensions:
            search_result.append(os.path.join(curdir, file))
      write_info(music_info_file, search_result)
    elif command == 'tag':
      md5 = command_line.split()[1]
      tag = command_line.split()[2]
      add_tag_by_md5(music_list, md5, tag)
    elif command == 'tagsong':
      song = command_line.split()[1]
      tag = command_line.split()[2]
      add_tag_by_song(music_list, song, tag)
    elif command == 'list':
      word = command_line.split()[1]
      list_musics(music_list, music_root, words, alias, word)
    else:
      print('Invalid command')
  
  print('Exiting')
  
  # Postprocess
  WriteMusicList(music_list_file, music_list)
  GenerateConfiguration(music_config_file, words, alias)


if __name__ == '__main__':
  main()
