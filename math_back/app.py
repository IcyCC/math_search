import ctypes
from flask import Flask, request, jsonify
so = ctypes.CDLL('./sum.so')

app = Flask(__name__)

@app.route("/search", methods=["POST"])
def r_search():
    pass

