# -*- coding: utf-8 -*-
# @Time    : 2019/8/4 16:19
# @Author  : J.K LuMinzhe
# @Site    : 
# @File    : manager.py
# @Software: PyCharm

import os
import sys
import math
import time
import json
import shutil
import collections

import io_util
import functions

from dictionary import *


def get_local_conf(local_conf):
  if not os.path.exists(local_conf):
    return dict(), dict()
  
  load_conf = json.load(open(local_conf, 'r', encoding='utf-8'), object_pairs_hook=collections.OrderedDict)
  return load_conf['WORDS'], load_conf['ALIAS']

def get_local_list(local_list):
  if not os.path.exists(local_list):
    return dict()
  
  return json.load(open(local_list, 'r', encoding='utf-8'), object_pairs_hook=collections.OrderedDict)

def save_local_conf(local_conf, words, alias):
  outstream          = collections.OrderedDict()
  outstream['WORDS'] = words
  outstream['ALIAS'] = alias
  json.dump(outstream, open(local_conf, 'w', encoding='utf-8'), ensure_ascii=False, indent=4)

def save_local_list(local_list, file_list):
  write_list = collections.OrderedDict()
  for md5 in sorted(file_list, key=lambda d: (d[1], d[0])):
    write_list[md5] = file_list[md5]
  json.dump(write_list, open(local_list, 'w', encoding='utf-8'), ensure_ascii=False, indent=4)

def read_staging(staging_list, tag_config):
  if not os.path.exists(staging_list):
    return collections.OrderedDict()
  
  staging = collections.OrderedDict()
  nonsense_lines = []
  for line in open(staging_list, 'r', encoding='utf-8').read().strip('\n').split('\n'):
    items = line.strip('\t').split('\t')
    if len(items) <= 2:
      nonsense_lines.append(line)
      continue
    
    staging_file = collections.OrderedDict()
    staging_file['md5'] = items[0]
    staging_file['file'] = items[1]
    if len(items) == 2:
      staging_file['new_name'] = staging_file['file'].split('\\')[-1]
    else:
      if len(items) > 3 + len(tag_config):
        items[2 + len(tag_config)] = ';'.join(items[2 + len(tag_config):])
      else:
        for i in range(3 + len(tag_config) - len(items)):
          items.append('')
      staging_file['new_name'] = items[2]
      for tag_name, i in zip(tag_config, range(3, 3 + len(tag_config))):
        if tag_config[tag_name] == 'item':
          staging_file[tag_name] = items[i]
        else:
          staging_file[tag_name] = items[i].split(';')
    staging[staging_file['md5']] = staging_file
  return staging, nonsense_lines


def write_staging(staging_list, staging, nonsense_lines, tag_config):
  output_lines = nonsense_lines
  for md5 in staging:
    staging_file = staging[md5]
    line = md5 + '\t' + staging_file['file'] + '\t' + staging_file['new_name']
    for key in tag_config:
      if tag_config[key] == 'item':
        line += '\t' + staging_file[key]
      else:
        line += '\t' + ';'.join(staging_file[key])
    output_lines.append(line)
  open(staging_list, 'w', encoding='utf-8').write('\n'.join(output_lines))


def search_filename(file_list, name):
  for md5 in file_list:
    if file_list[md5]['file'].split('\\')[-1] == name:
      return True
  return False


# 检查要添加文件的标签是否合适
def check_file(file_list, words, alias, staging_file, tag_config):
  for key in tag_config:
    wordset = staging_file[key]
    if tag_config[key] == 'item':
      wordset = [wordset]
    for word in wordset:
      if word != '':
        if word not in words and word not in alias:
          print('new word %s, please add it before adding this new file' % word)
          return False
        if word in alias:
          word = alias[word]
        if words[word] != key:
          print('the word %s has another type in dictionary as %s, not %s' % (word, words[word], key))
          return False
  
  # check md5
  md5 = staging_file['md5']
  if md5 in file_list and staging_file['file'] != file_list[md5]['file']:
    print('File repeated: %s' % staging_file['file'].split('\\')[-1])
    return False
  return True


def move_and_update_file(file, alias, staging_file, config):
  tag_config = config['Tags']
  
  if file['file'] != staging_file['file']:
    if len(tag_config) >= 1:
      first_key = list(tag_config.keys())[0]
      value = staging_file[first_key]
      if tag_config[first_key] != 'item':
        if len(value) > 0:
          value = value[0]
        else:
          value = ''
    else:
      value = staging_file['new_name']
    dirname = 'AutoDir_' + functions.get_first_letter(value)
    new_dir = os.path.join(config['RootPath'], dirname)
    new_file = os.path.join(new_dir, staging_file['new_name'])
    
    # check repeated name
    rename = new_file
    repeat_num = 1
    while os.path.exists(rename):
      rename = new_file + '_%d' % repeat_num
      repeat_num += 1
    new_file = rename
    
    # move file
    if not os.path.exists(new_dir):
      os.makedirs(new_dir)
    shutil.move(staging_file['file'], new_file)
  else:
    new_file = file['file']
  
  file['md5'] = staging_file['md5']
  file['file'] = new_file
  file['name'] = new_file.split('\\')[-1]
  for key in tag_config:
    if tag_config[key] == 'item':
      if staging_file[key] in alias:
        staging_file[key] = alias[staging_file[key]]
      file[key] = staging_file[key]
    else:
      for value in staging_file[key]:
        if value not in file[key]:
          if value in alias:
            value = alias[value]
          file[key].append(value)


def add_staging_list(file_list, words, alias, staging, config):
  tag_config = config['Tags']
  success_md5 = []
  for md5 in staging:
    ret = check_file(file_list, words, alias, staging[md5], tag_config)
    if not ret:
      continue
    
    if md5 not in file_list:
      file_list[md5] = build_tagged_dict(tag_config)
    move_and_update_file(file_list[md5], alias, staging[md5], config)
    success_md5.append(md5)
  
  for md5 in success_md5:
    staging.pop(md5)


def add_tag_to_config(words, alias, tag_word, type_word, tag_config):
  if type_word not in tag_config:
    print('Donot support the type %s' % type_word)
    return
  
  if tag_word in words or tag_word in alias:
    if tag_word in alias:
      tag_word = alias[tag_word]
    
    if words[tag_word] != type_word:
      confirm = input("The word's original type is %s, do you confirm to use the new type? yes | no" % words[tag_word])
      if confirm == 'yes':
        words[tag_word] = type_word
  else:
    words[tag_word] = type_word


def add_alias_to_config(words, alias, alias_word, tag_word):
  if alias_word in alias:
    print('Already has this alias, its tag_word is %s, please remove it before changing the tag_word' % alias[alias_word])
    return
  
  if tag_word in alias:
    tag_word = alias[tag_word]
  
  if tag_word not in words:
    print('The tag_word is not in dictionary, please add it before adding its alias')
  else:
    alias[alias_word] = tag_word


def search_dir(dir, exts, tag_config):
  search_result = dict()
  for curdir, subdir, files in os.walk(dir):
    for file in files:
      if io_util.get_extension(file) in exts:
        md5 = io_util.get_md5(os.path.join(curdir, file))
        search_result[md5] = build_tagged_dict(tag_config)
        search_result[md5]['md5'] = md5
        search_result[md5]['file'] = os.path.join(curdir, file)
        search_result[md5]['new_name'] = file
  return search_result
        
def list_total_list(file_list, tag_config):
  for md5 in file_list:
    file = file_list[md5]
    line = []
    line.append(file['md5'])
    line.append(file['file'])
    line.append(file['name'])
    for tag in tag_config:
      if tag_config[tag] == 'item':
        line.append(file[tag])
      else:
        line.append(';'.join(file[tag]))
    print('\t'.join(line))

def find_files_to_tmp(file_list, words, alias, tag_config, tmp_dir, word):
  if word in alias:
    word = alias[word]
  if word not in words:
    print('Cannot find', word)
    return

  tag = words[word]
  if tag not in tag_config:
    raise('Error, the %s is not in tag_config' % tag)
  
  filters = []
  for md5 in file_list:
    file = file_list[md5]
    if tag_config[tag] == 'item':
      if file[tag] == word:
        filters.append(md5)
    else:
      if word in file[tag]:
        filters.append(md5)
  
  for md5 in filters:
    file = file_list[md5]
    io_util.create_link(file['file'], os.path.join(tmp_dir, file['name']))

def write_ttpl(tmp_dir):
  files = []
  for dir, subdir, fs in os.walk(tmp_dir):
    for f in fs:
      if f.endswith('.lnk'):
        ft = io_util.get_target_from_link(os.path.join(dir, f))
        files.append([ft, f[:-4]])
    break
  
  output_ttpl = open(os.path.join(tmp_dir, 'tmp.ttpl'), 'w', encoding='utf-8')
  output_ttpl.write('<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>\n')
  output_ttpl.write('<ttplaylist title="tmp" version="4" generator="TTPlayer -- 5.7.8">\n')
  output_ttpl.write('	<format tagtitle="%A - %T" deftitle="%F"/>\n')
  output_ttpl.write('	<items count="%d">\n' % len(files))
  for file in files:
    output_ttpl.write('		<item file="%s" title="%s"/>\n' % (file[0], file[1]))
  output_ttpl.write('	</items>\n')
  output_ttpl.write('</ttplaylist>\n')