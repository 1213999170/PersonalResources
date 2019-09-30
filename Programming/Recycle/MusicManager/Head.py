# -*- coding: utf-8 -*-
# @Time    : 2019/4/28 1:52
# @Author  : J.K LuMinzhe
# @Site    : 
# @File    : Head.py
# @Software: PyCharm

import os
import sys
import math
import time
import json
import collections

import functions

import MusicInfo

MUSIC_LIST_STAGING = r'F:\Music\music_list_staging.txt'
MUSIC_LIST = r'F:\Music\music_list.txt'

MUSIC_FILE_EXT = [
  'mp3',
  'wav',
]

def JudgeMusicFile(file):
  if '.' in file and file[-1] != '.':
    file_ext = file.split('.')[-1]
  
  return file_ext in MUSIC_FILE_EXT


def ReadMusicList(file):
  music_list = dict()
  if os.path.exists(file):
    read_list = json.load(open(file, 'r'), object_pairs_hook=collections.OrderedDict)
    for key in read_list:
      music = read_list[key]
      music_info = MusicInfo.MusicInfo(music)
      functions.add_to_dict(base=music_list, key=music['md5'], value=music_info, checkRepeat=True)
  return music_list


def WriteMusicList(music_list, file):
  write_list = collections.OrderedDict()
  for music in sorted(music_list.items(), key=lambda d: (d[1].name, d[0])):
    write_list[music[0]] = music[1].get_dict()
  json.dump(write_list, open(file, 'w'), ensure_ascii=False, indent=4)


