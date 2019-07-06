import pyinterface

QueryTypeMap = {
    "text": 3,
    "nature": 0,
    "excries": 2,
    "concept": 1,
    "example": 4
}


def QueryCommPy(q, t):
    # 有理数
    res = pyinterface.QueryCommPy(q, QueryTypeMap.get(t, 1))
    return list([{
        "id": r.id,
        "chapter": r.chapter,
        "title": r.title,
        "raw": r.raw,
        "abstract": r.summary
    } for r in res])


def SegmentWords(text):
    return pyinterface.SegmentWords(text)
