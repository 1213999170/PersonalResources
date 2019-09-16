# -*- coding: utf-8 -*-
# @Time    : 2018/10/20 0020 22:08
# @Author  : J.K LuMinzhe
# @Site    : 
# @File    : bb.py
# @Software: PyCharm

import os
import sys
import math
import time

import requests_html
import io_util
from requests_html import HTML
import hashlib
import random

import hashlib

import urllib.request
import urllib
import pythoncom
import winshell
import win32com.client as client
shell = client.Dispatch("WScript.Shell")

import functions

def main():
  words = functions.split_command_line("search 'F:\\Music\\Singer X Y Z'")
  print(words)
  

if __name__ == '__main__':
  main()
