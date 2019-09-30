# -*- coding: utf-8 -*-
# @Time    : 2019/4/28 2:10
# @Author  : J.K LuMinzhe
# @Site    : 
# @File    : Op2_AddToMusicList.py
# @Software: PyCharm

import os
import sys
import math
import time
import json

import functions
import io_util

import Head
import MusicInfo


def GetMusicList(inputfile):
  music_infos = open(inputfile, 'r').read().strip('\n').split('\n')
  musics = dict()
  for music_info in music_infos:
    music_info = music_info.split('\t')
    md5        = music_info[0]
    pathfile   = music_info[1]
    title      = music_info[2]
    singer     = music_info[3]
    language   = music_info[4]
    favor      = music_info[5]
    tags       = ''
    if len(music_info) > 6:
      tags     = ','.join(music_info[6:])
    
    # rename file
    path         = '\\'.join(pathfile.split('\\')[:-1])
    new_pathfile = os.path.join(path, title)
    os.rename(pathfile, new_pathfile)
    
    # create a MusicInfo instance
    music          = MusicInfo.MusicInfo()
    music.md5      = md5
    music.name     = title
    music.file     = new_pathfile
    music.singer   = singer
    music.language = language
    music.tags     = tags
    music.favor    = favor

    functions.add_to_dict(base=musics, key=md5, value=music, checkRepeat=True)
  return musics


def UpdateMusicInfo(old_music, new_music):
  if old_music.name != new_music.name:
    print('Reset music.name from', old_music.name, 'to', new_music.name)
    old_music.name = new_music.name
  if old_music.singer != new_music.singer:
    print('Reset music.singer from', old_music.singer, 'to', new_music.singer)
    old_music.singer = new_music.singer
  if old_music.language != new_music.language:
    print('Reset music.language from', old_music.language, 'to', new_music.language)
    old_music.language = new_music.language
  if old_music.favor != new_music.favor:
    print('Reset music.favor from', old_music.favor, 'to', new_music.favor)
    old_music.favor = new_music.favor
  if old_music.tags != new_music.tags:
    new_tags = set(old_music.tags.split(',') + new_music.tags.split(','))
    if len(new_tags) > 5:
      raise RuntimeError('The tag number of music is beyond 5, md5', new_music.md5)
    if len(old_music.tags.split(',')) < len(new_tags):
      print('Reset music.tags from', old_music.tags, 'to', new_tags)
      old_music.tags = ','.join(new_tags)


def AddToMusicList(musics, music_list):
  for key in musics:
    music = musics[key]
    if key in music_list:
      if music.file == music_list[key].file or not os.path.exists(music_list[key].file):
        UpdateMusicInfo(music_list[key], music)
      else:
        raise RuntimeError('Find repeat music file, md5', md5)
    else:
      music_list[key] = music
  


def main():
  print('hello')
  musics = GetMusicList(r'F:\Music\cur_music_list.txt')
  music_list = Head.ReadMusicList(Head.MUSIC_LIST_STAGING)
  AddToMusicList(musics, music_list)
  Head.WriteMusicList(music_list, Head.MUSIC_LIST_STAGING)
  print('welcome')


if __name__ == '__main__':
  main()
