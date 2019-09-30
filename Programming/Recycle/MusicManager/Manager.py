# -*- coding: utf-8 -*-
# @Time    : 2019/3/31 15:21
# @Author  : J.K LuMinzhe
# @Site    : 
# @File    : Manager.py
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

import MusicInfo


def InitConfiguration(music_config_file):
  music_config = json.load(open(music_config_file, 'r'), object_pairs_hook=collections.OrderedDict)
  return music_config['WORDS'], music_config['ALIAS']


def GenerateConfiguration(music_config_file, words, alias):
  outstream          = collections.OrderedDict()
  outstream['WORDS'] = words
  outstream['ALIAS'] = alias
  json.dump(outstream, open(music_config_file, 'w'), ensure_ascii=False, indent=4)


def GetMusicList(music_list_file):
  music_list = dict()
  if not os.path.exists(music_list_file):
    return music_list
  
  read_dict = json.load(open(music_list_file, 'r'), object_pairs_hook=collections.OrderedDict)
  for md5 in read_dict:
    music = read_dict[md5]
    if os.path.exists(music['file']):
      functions.add_to_dict(music_list, music['md5'], MusicInfo.MusicInfo(music), True)
  return music_list


def WriteMusicList(music_list_file, music_list):
  write_list = collections.OrderedDict()
  for md5 in sorted(music_list, key=lambda d: (d[1], d[0])):
    music = music_list[md5]
    write_list[md5] = music.get_dict()
  json.dump(write_list, open(music_list_file, 'w'), ensure_ascii=False, indent=4)


# Tools

def write_info(music_info_file, search_result):
  fout = open(music_info_file, 'w', encoding='utf-8')
  for music in search_result:
    md5 = io_util.get_md5(music)
    music_name = music.split('\\')[-1]
    fout.write(md5 + '\t' + music + '\t' + music_name + '\n')


def classify_words(words):
  Extensions = []
  for key, value in words.items():
    if value == 'Ext':
      Extensions.append(key)
  return Extensions


def move_to_new_path(file, new_name, music_root):
  dirname = 'MusicStorage_' + functions.get_first_letter(new_name, 2)
  new_dir = os.path.join(music_root, dirname)
  if not os.path.exists(new_dir):
    os.makedirs(new_dir)
  newfile = os.path.join(new_dir, new_name)
  shutil.move(file, newfile)
  return newfile


def check_alias(word, alias, words, word_type):
  if word in alias:
    alias_word = alias[word]
    if words[alias_word] != word_type:
      raise RuntimeError('The alias of ' + word + ' is ' + alias_word
                         + ', but it is a ' + words[alias_word] + ', not a ' + word_type)
    return alias[word]
  return word
  

def check_word(new_word, words, word_type):
  if new_word in words:
    if words[new_word] != word_type:
      raise RuntimeError(word_type + ' [' + new_word + '] is a ' + words[new_word] + ' in current dictionary')
    else:
      pass
  else:
    words[new_word] = word_type

def add_music(music_list, music_add_file, music_root, words, alias):
  lines = open(music_add_file, 'r', encoding='utf-8').read().split('\n')
  if len(lines) > 20:
    raise RuntimeError('Add too much songs')
  
  for line in lines:
    items = line.strip('\t').split('\t')
    if len(items) < 6:
      continue
    
    md5, file, new_name, singers, language, favor = items[0:6]
    singers = singers.strip(';').split(';')
    
    # Check alias and words
    for i in range(len(singers)):
      singers[i] = check_alias(singers[i], alias, words, 'Singer')
    language = check_alias(language, alias, words, 'Language')
    favor = check_alias(favor, alias, words, 'Favor')
    for tag in items[6:]:
      tag = check_alias(tag, alias, words, 'Tag')
    
    for singer in singers:
      check_word(singer, words, 'Singer')
    check_word(language, words, 'Language')
    check_word(favor, words, 'Favor')
    for tag in items[6:]:
      check_word(tag, words, 'Tag')
    
    # Move to default path and create music
    newfile = move_to_new_path(file, new_name, music_root)
    music = {}
    music['md5']      = md5
    music['file']     = newfile
    music['name']     = new_name
    music['singers']  = singers
    music['language'] = language
    music['favor']    = favor
    music['tags']     = items[6:]
    
    functions.add_to_dict(music_list, music['md5'], MusicInfo.MusicInfo(music), True)


def search_music(music_list, song):
  ret = 0
  
  for md5 in music_list:
    music = music_list[md5]
    if song == music['name']:
      if ret == 0:
        ret = music
      else:
        return -1
  
  if ret != 0:
    return ret
  
  for md5 in music_list:
    music = music_list[md5]
    if song in music['name']:
      if ret == 0:
        ret = music
      else:
        return -1
  
  return ret


def add_tag_by_song(music_list, song, tag):
  music = search_music(music_list, song)
  if music == 0:
    print('Cannot find the song')
  elif music == -1:
    print('Cannot determine the song')
  else:
    add_tag_by_md5(music_list, music['md5'], tag)


def add_tag_by_md5(music_list, md5, tag):
  if md5 not in music_list:
    print('the md5 cannot be found')
  else:
    if tag not in music_list[md5]['tag']:
      music_list[md5]['tag'].append(tag)
    else:
      print('the song already has the tag')


def list_musics(music_list, music_root, words, alias, word):
  if word in alias:
    word = alias[word]
  if word not in words:
    print('Do not have the word yet')
  
  

