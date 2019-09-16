# -*- coding: utf-8 -*-
# @Time    : 2019/8/4 14:28
# @Author  : J.K LuMinzhe
# @Site    : 
# @File    : main.py
# @Software: PyCharm

import os
import sys
import math
import time
import shutil
import traceback

from dictionary import *
from manager import *

def main_process(workitem, config):
  # List Path&Files
  root = config['RootPath']
  local_conf = os.path.join(root, 'conf.json')
  local_list = os.path.join(root, 'list.json')
  sys_dir = os.path.join(root, 'system')
  tmp_dir = os.path.join(root, 'qianqian')
  local_staging = os.path.join(root, 'staging.txt')
  
  # Backup config and list files
  time_pattern = time.strftime('%Y%m%d_%H%M%S', time.localtime())
  bak_conf = os.path.join(sys_dir, 'conf_bak%s.json' % time_pattern)
  bak_list = os.path.join(sys_dir, 'list_bak%s.json' % time_pattern)
  if os.path.exists(local_conf) and os.path.exists(local_list):
    shutil.copy(local_conf, bak_conf)
    shutil.copy(local_list, bak_list)
  
  # Preprocess
  words, alias = get_local_conf(local_conf)
  exts = get_words_by_type(words, alias, type = 'ext', include_alias = True)
  file_list = get_local_list(local_list)
  
  try:
    # MainProcess
    while True:
      command_line = input('$ ')
      if not command_line:
        continue
      commands = functions.split_command_line(command_line)
      command = commands[0]
      
      if command == 'h' or command == 'help':
        print('Commands:')
        print('h | help : print help info')
        print('q | quit | exit : terminate TagManager')
        print('at | addtag [tag_word] [type_word] : add tag into config file')
        print('aa | addalias [alias_word] [tag_word] : add alias into config file')
        print('a | add : add staging list to list file')
        print('s | search [dir] : find music files and list them to staging list file')
        print('l | list : list total music')
        print('f | find [word] : find music and create link in tmp_dir')
        print('m | makelist : make a ttpl for QianQian player')
      elif command == 'q' or command == 'quit' or command == 'exit':
        break
      elif command == 'at' or command == 'addtag':
        if len(commands) != 3:
          print('Invalid command')
          continue
        tag_word = commands[1]
        type_word = commands[2]
        add_tag_to_config(words, alias, tag_word, type_word, config['Tags'])
      elif command == 'aa' or command == 'addalias':
        if len(commands) != 3:
          print('Invalid command')
          continue
        alias_word = commands[1]
        tag_word = commands[2]
        add_alias_to_config(words, alias, alias_word, tag_word)
      elif command == 'a' or command == 'add':
        if len(commands) != 1:
          print('Invalid command')
          continue
        staging, nonsense_lines = read_staging(local_staging, config['Tags'])
        add_staging_list(file_list, words, alias, staging, config)
        write_staging(local_staging, staging, nonsense_lines, config['Tags'])
      elif command == 's' or command == 'search':
        if len(commands) != 2:
          print('Invalid command')
          continue
        dir = commands[1]
        staging = search_dir(dir, exts, config['Tags'])
        write_staging(local_staging, staging, [], config['Tags'])
      elif command == 'l' or command == 'list':
        if len(commands) != 1:
          print('Invalid command')
          continue
        list_total_list(file_list, config['Tags'])
      elif command == 'f' or command == 'find':
        if len(commands) != 2:
          print('Invalid command')
          continue
        word = commands[1]
        find_files_to_tmp(file_list, words, alias, config['Tags'], tmp_dir, word)
      elif command == 'm' or command == 'makelist':
        if len(commands) != 1:
          print('Invalid command')
          continue
        write_ttpl(tmp_dir)
      else:
        print('Invalid command')
    print('Exiting')
  except:
    traceback.print_exc()
  finally:
    # Postprocess
    save_local_list(local_list, file_list)
    save_local_conf(local_conf, words, alias)


def main():
  config = json.load(open(r'config.json', 'r'), object_pairs_hook=collections.OrderedDict)
  while (True):
    workitem = input(r'Please choose a workitem: %s' % '\t'.join(config.keys()))
    
    if not workitem:
      workitem = 'Music'
    
    if workitem in config:
      break
    print(r'Your choice is not supported')
  
  main_process(workitem, config[workitem])


if __name__ == '__main__':
  main()
