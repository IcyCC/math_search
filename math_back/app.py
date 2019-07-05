import ctypes
from flask import Flask, request, jsonify, redirect, make_response
import os
import mock
from relation import data as key_word_data
import interface

be_mock = False
service = interface

if be_mock:
    service = mock

path = os.path.split(os.path.abspath(__file__))[0]
app = Flask(__name__, static_folder=os.path.join(path, 'static'))


BOOK_INDEX = res = [{'title': '1.1 正数和负数', 'page': '8'},
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

book_map = [{'range': (111, 115), 'name': 'book111-115.tex'},
            {'range': (51, 56), 'name': 'book51-56.tex'},
            {'range': (6, 10), 'name': 'book6-10.tex'},
            {'range': (56, 60), 'name': 'book56-60.tex'},
            {'range': (86, 90), 'name': 'book86-90.tex'},
            {'range': (26, 30), 'name': 'book26-30.tex'},
            {'range': (101, 105), 'name': 'book101-105.tex'},
            {'range': (11, 15), 'name': 'book11-15.tex'},
            {'range': (16, 20), 'name': 'book16-20.tex'},
            {'range': (66, 70), 'name': 'book66-70.tex'},
            {'range': (36, 40), 'name': 'book36-40.tex'},
            {'range': (40, 45), 'name': 'book40-45.tex'},
            {'range': (96, 100), 'name': 'book96-100.tex'},
            {'range': (106, 110), 'name': 'book106-110.tex'},
            {'range': (61, 65), 'name': 'book61-65.tex'},
            {'range': (46, 50), 'name': 'book46-50.tex'},
            {'range': (31, 35), 'name': 'book31-35.tex'},
            {'range': (91, 95), 'name': 'book91-95.tex'},
            {'range': (21, 25), 'name': 'book21-25.tex'},
            {'range': (81, 85), 'name': 'book81-85.tex'}]


@app.route("/search", methods=["POST"])
def r_search():
    body = request.json
    query_text = body.get("query_text", '')
    query_type = body.get("query_type", 'concept')
    res = service.QueryCommPy(query_text, query_type)

    return jsonify(code=200, msg='', data=res)


@app.route("/getKeyWord", methods=["GET"])
def get_key_word():
    d = list(key_word_data.keys())
    return jsonify(code=200, msg="", data=d)


@app.route("/segmentWords", methods=["POST"])
def segment_words():
    body = request.json
    text = body.get('text', '')
    d = service.SegmentWords(text=text)
    return jsonify(code=200, msg="", words=d)


@app.route("/getBookIndex", methods=["GET"])
def get_book_index():
    return jsonify(code=200, msg="", book_index=BOOK_INDEX)


@app.route("/bookPage/<int:page>", methods=["GET"])
def book_page(page):
    p = page - 5
    for l in book_map:
        if l['range'][0] <= p <=l['range'][1]:
            d = ''
            with open(os.path.join(app.static_folder, 'latex', l['name']), 'r') as f:
                d = f.read()

            return d, 200
    return '', 200

def run():
    app.run(port=5001)

if __name__ == "__main__":
    run()
