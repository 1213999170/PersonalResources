from xpinyin import Pinyin

def getPinyin(string):
  a = Pinyin()
  b = a.get_pinyin(u'你好Jack,欢迎，来上海', '')
  print(b)


if __name__ == '__main__':
  getPinyin('非场')