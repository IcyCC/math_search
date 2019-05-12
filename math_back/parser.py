import re
import lxml

s= """
"""

ht = lxml.etree.HTML(s)
def parser_page(s):
    return re.findall('ebook\/(.*?).html', s)


res = [ {'title':i.text, 'page':  parser_page(i.attrib['href'])[0] } for i in  ht.xpath('//ul[@class="t-bd"]//div[@class="t-name"]/a')]

res = [{'title': '1.1 正数和负数', 'page': '8'},
 {'title': '1.2 有理数', 'page': '12'},
 {'title': '1.2.1 有理数', 'page': '12'},
 {'title': '1.2.2 数轴', 'page': '13'},
 {'title': '1.2.3 相反数', 'page': '15'},
 {'title': '1.2.4 绝对值', 'page': '17'},
 {'title': '1.3 有理数的加减法', 'page': '22'},
 {'title': '1.3.1 有理数的加法', 'page': '22'},
 {'title': '1.3.2 有理数的减法', 'page': '27'},
 {'title': '1.4 有理数的乘除法', 'page': '34'},
 {'title': '1.4.1 有理数的乘法', 'page': '34'},
 {'title': '1.4.2 有理数的除法', 'page': '40'},
 {'title': '1.5 有理数的乘方', 'page': '47'},
 {'title': '1.5.1 乘方', 'page': '47'},
 {'title': '1.5.2 科学记数法', 'page': '50'},
 {'title': '1.5.3 近似数', 'page': '51'},
 {'title': '第二章 整式的加减', 'page': '59'},
 {'title': '2.1 整式', 'page': '60'},
 {'title': '2.2 整式的加减', 'page': '59'},
 {'title': '第三章 一元一次方程', 'page': '83'},
 {'title': '3.1 从算式到方程', 'page': '84'},
 {'title': '3.1.1 一元一次方程', 'page': '84'},
 {'title': '3.1.2 等式的性质', 'page': '87'},
 {'title': '3.2 解一元一次方程（一）----合并同类项与移项', 'page': '92'},
 {'title': '3.3 解一元一次方程（二）----去括号与去分母', 'page': '99'},
 {'title': '3.4 实际问题与一元一次方程', 'page': '106'},
 {'title': '第四章 几何图形初步', 'page': '119'},
 {'title': '4.1 几何图形', 'page': '120'},
 {'title': '4.1.1 立体图形与平面图形', 'page': '121'},
 {'title': '4.1.2 点、线、面、体', 'page': '125'},
 {'title': '4.2 直线、射线与线段', 'page': '131'},
 {'title': '4.3 角', 'page': '138'},
 {'title': '4.3.1 角', 'page': '138'},
 {'title': '4.3.2 角的比较与运算', 'page': '140'},
 {'title': '4.3.3 余角和补角', 'page': '143'},
 {'title': '4.4 课题学习 设计制作长方体形状的包装纸盒', 'page': '148'}]
