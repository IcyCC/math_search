import ctypes
from flask import Flask, request, jsonify

mock = True

app = Flask(__name__, static_folder='/Users/suchang/Code/homework/math_search/math_back/static')

@app.route("/search", methods=["POST"])
def r_search():
    res =  [{
    "id":1,
    "chapter":"1.1.1 有理数",
    "title":"有理数的性质",
    "raw":"有理数是一个数",
    "abstract": [
        "有理数是一个数",
        "无线不循环的有理数"
    ]
}, 
{
    "id":2,
    "chapter":"1.1.1 无理数",
    "title":"无理数",
    "raw":"有无理数不好吃",
    "abstract": [
           "无理数是一个数",
        "无线不循环的无理数"
    ]
}]

    return jsonify(code=200, msg='', data=res)


@app.route("/getKeyWord", methods = ["GET"])
def get_key_word():

    d= [
        "有理数",
        "本质",
        "物理"
    ]
    return jsonify(code=200, msg="", data=d)


@app.route("/segmentWords", methods = ["POST"])
def segment_words():

    d= [
        "有理数",
        "本质",
        "物理"
    ]
    return jsonify(code=200, msg="", words=d)


if __name__ == "__main__":
    app.run()


