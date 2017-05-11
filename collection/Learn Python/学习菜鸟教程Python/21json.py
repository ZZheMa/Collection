# -*- coding: utf-8 -*-

import json;

# 1.json.dumps 用于将 Python 对象编码成 JSON 字符串。
data = [{'a':1, 'b':2, 'c':3, 'd':4}]
json_str = json.dumps(data)
print json_str

# 使用参数让 JSON 数据格式化输出：
json_str = json.dumps(data, sort_keys = True, indent = 4, separators = (",",": "))
print json_str

# 2.json.loads 用于解码 JSON 数据。该函数返回 Python 字段的数据类型。
data = '{"a":1, "b":2}'
text = json.loads(data)
print text