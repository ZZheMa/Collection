# -*-coding: utf-8 -*-

# 1.Dom解析器
# 一个 DOM 的解析器在解析一个 XML 文档时，一次性读取整个文档，
# 把文档中所有元素保存在内存中的一个树结构里，之后你可以利用DOM
# 提供的不同的函数来读取或修改文档的内容和结构，也可以把修改过的
# 内容写入xml文件。

# 类似于C++中的TinyXml等。

from xml.dom.minidom import parse
import xml.dom.minidom

# 使用minidom打开并解析xml，解析得到的树放在变量tree中。
tree = xml.dom.minidom.parse("20movies.xml")

# collection是根节点，其余所有的元素都在这个节点下面。
collection = tree.documentElement
# 获取该节点的属性。
if collection .hasAttribute("shelf"):
  print "Root element : %s " % collection .getAttribute("shelf");

# 获得collection节点下面所有的movie节点，返回一个数组。
movies = collection .getElementsByTagName("movie")

# 遍历每个movie节点。
for movie in movies:
  print "*****Movie*****"

  if movie.hasAttribute("title"):
    print "Title: %s " % movie.getAttribute("title")

  # 获取movie节点下面的第一个tpye节点，因为其他情况中可能有多个type节点，所以使用索引[0]
  type = movie.getElementsByTagName("type")[0]
  # 获取type节点的内容节点。
  print "Type: % s " % type.childNodes[0].data
  format = movie.getElementsByTagName('format')[0]
  print "Format: %s" % format.childNodes[0].data
  rating = movie.getElementsByTagName('rating')[0]
  print "Rating: %s" % rating.childNodes[0].data
  description = movie.getElementsByTagName('description')[0]
  print "Description: %s" % description.childNodes[0].data