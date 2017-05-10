# -*-coding: utf-8 -*-

# 1.SAX解析器
# SAX是一种基于事件驱动的API。
# 利用SAX解析XML文档牵涉到两个部分:解析器和事件处理器。
# 解析器负责读取XML文档,并向事件处理器发送事件,如元素开始跟元素结束事件;
# 而事件处理器则负责对事件作出相应,对传递的XML数据进行处理。
# 我们要做的就是重写事件处理器的方法。

# 应用场景：
# (A)对大型文件进行处理；
# (B)只需要文件的部分内容，或者只需从文件中得到特定信息。
# (C)想建立自己的对象模型的时候。

# ContentHandler类方法介绍
# (A)characters(content)方法
# 调用时机：
# 从行开始，遇到标签之前，存在字符，content的值为这些字符串。
# 从一个标签，遇到下一个标签之前， 存在字符，content的值为这些字符串。
# 从一个标签，遇到行结束符之前，存在字符，content的值为这些字符串。
# 标签可以是开始标签，也可以是结束标签。
# (B)startDocument()方法
# 文档启动的时候调用。
# (C)endDocument()方法
# 解析器到达文档结尾时调用。
# (D)startElement(name, attrs)方法
# 遇到XML开始标签时调用，name是标签的名字，attrs是标签的属性值字典。
# (E)endElement(name)方法
# 遇到XML结束标签时调用。

import xml.sax

class MovieHandler(xml.sax.ContentHandler):
  def __init__(self):
    self.CurrentTag = ""
    self.type = ""
    self.format = ""
    self.year = ""
    self.rating = ""
    self.stars = ""
    self.description = ""

  # 当开始解析每个元素开始时，触发该事件。每个元素也就是<element/>或者<element></element>
  # 参数tag是个字符串，也就是element的名字，attrs是一个数组，是该element的属性。
  # 总结：如果要得到一个element的name和attribute，要在startElement中获取。
  def startElement(self, tag, attrs):
    self.CurrentTag = tag
    if tag == "movie":
      print "*****Movie*****"
      title = attrs["title"]
      print "Title: ", title

  # 当解析完一个元素的时候，触发该事件。
  # 总结：因为元素是可以层层嵌套的，所以区分是哪个元素结束，
  # 那么可以用一个if语句来判断，因为参数tag是当前结束的元素的名字。
  def endElement(self, tag):
    if tag == "type":
      print "Type: ", self.type;
    elif tag == "format":
      print "Format:", self.format
    elif tag == "year":
       print "Year:", self.year
    elif tag == "rating":
       print "Rating:", self.rating
    elif tag == "stars":
       print "Stars:", self.stars
    elif tag == "description":
       print "Description:", self.description

  # 当解析到元素的value时，也就是元素的内容时，触发该事件。
  def characters(self, content):
    if self.CurrentTag == "type":
      self.type = content;
    elif self.CurrentTag == "format":
      self.format = content;
    elif self.CurrentTag == "year":
      self.year = content;
    elif self.CurrentTag == "rating":
      self.rating = content
    elif self.CurrentTag == "stars":
      self.stars = content
    elif self.CurrentTag == "description":
      self.description = content

if __name__ == '__main__':
  # 创建一个sax解析器。
  parser = xml.sax.make_parser()
  # 关闭命名空间，xml是有命名空间的。
  parser.setFeature(xml.sax.handler.feature_namespaces, 0)

  # 创建Movie ContentHandler。
  movie_handler = MovieHandler()
  # 给解析器设置handler。
  parser.setContentHandler(movie_handler)

  # 进行解析。
  parser.parse("20movies.xml")