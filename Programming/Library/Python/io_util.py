# -*- coding: utf-8 -*-
# @Time    : 2018/10/21 0021 00:13
# @Author  : J.K LuMinzhe
# @Site    : 
# @File    : io_util.py
# @Software: PyCharm

import os
import hashlib

import win32com.client as client
shell = client.Dispatch("WScript.Shell")

def append_oneline_to_file(output_file, context):
  open(output_file, 'a').write(str(context) + '\n')

def get_md5(file):
  md = hashlib.md5()
  md.update(open(file, 'rb').read())
  return md.hexdigest()

def get_extension(file):
  ext = os.path.splitext(file)[-1]
  if ext.startswith('.'):
    return ext[1:]
  return ext

def create_link(source_file, link_file):
  if not link_file.endswith('lnk'):
    link_file += '.lnk'
  shortcut = shell.CreateShortCut(link_file)
  shortcut.TargetPath = source_file
  shortcut.save()
  
def get_target_from_link(link_file):
  shortcut = shell.CreateShortCut(link_file)
  return shortcut.Targetpath