# 数学搜索

## 架构
```
用户前端 -(http接口)--> web后端 --(.so)-->检索后台
```

```
公式处理后台
课本处理后台
```
## web前端

技术: vue axios

负责用户的交互, 提供一个舒适的交互界面, 并向后端发送请求, 把后端的相应展示出来

# web后端

技术: python pybind11  flask

负责处理前台的http请求, 并且调取静态资源或者后台系统的.so的接口, 进行查询

# 检索后台

读取处理过的文本，建立倒排索引。检索时对检索语句分词，然后根据倒排索引分别查询匹配的内容，进行合并、排序

# 公式处理后台

对公式进行处理, 进行公式的标准化和子公式提取, 传给检索后台

# 课本处理后台

对课本内容进行分块, 提取目录, 提取标题和处理关键词的关系


## 使用

### 依赖

```
python3
pybind11
nodejs
yarn
```

安装以来

```
pip3 install -r requirments.txt 
```

### 获取接口
```
cd src/
c++ -O3 -Wall -shared -std=c++11 -undefined dynamic_lookup `python3 -m pybind11 --includes` *.cpp -o pyinterface`python3-config --extension-suffix`
```

得到

pyinterface.so

放入math_back中

## 运行后端

```
cd math_back
python app.py
```
启动后端服务器

## 运行前端

```
cd math_front
yarn
yarn run dev
```

在浏览器中使用系统

## 功能实现

### 前端

使用vue 制作用户界面 , 用 axios 作为 http 请求的封装, 把用户的操作转为 http 请求发送给后端, 并把后端给的 http 响应显示出来

### 后端

后端是一个 python 的 HTTP 服务器, 采用 flask 编写, 接受到静态资源的 http 请求直接返回资源, 其余的通过.so 发送给检索后台. 最后返回一个 HTTP 响应


### 检索后台

#### 静态处理

把课本根据 latex 的标签分成不同的文件

#### 知识点处理

@lyf

#### 公式处理

1. 先对公式进行简化, 把 latex 符号转换成系统可以理解的 token

2. 根据 tokens构建公式树

3. 对公式树进行标准化, 根据父节点的运算符性质, 和左右节点的字典序, 判断是否对交换节点顺序

#### 分词处理

#### 检索处理

##### 索引

##### 摘要

