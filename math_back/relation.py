# coding=utf-8

import os
from gexf import Gexf

data = {}


def get_all_file(path):
    res = []
    for root, dirs, files in os.walk(path):
        for i in files:
            if i == '.DS_Stor' or (not i.endswith('q')):
                continue
            res.append(os.path.join(root, i))
    return res


for p in get_all_file('data'):
    with open(p, encoding='utf-8') as f:
        d = f.read()
        title = os.path.splitext( os.path.split(p)[1])[0]
        concepts = d.splitlines()
        for c in concepts:
            if c not in data:
                data[c] = []
        data[title] = list(concepts)

if __name__ == '__main__':

    my_gexf = Gexf('搜书网', '课本知识点图')
    g = my_gexf.addGraph("undirected", "static", "课本知识图谱")

    atr1 = g.addNodeAttribute('modularity_class', type='float', defaultValue=0)

    for d in data.keys():
        n = g.addNode(d, d)
        n.addAttribute(atr1, '1')
    edge_id = 0
    for d in data.keys():
        for c in data[d]:
            g.addEdge(str(edge_id), d, c)
            edge_id = edge_id + 1

    with open(r"/Users/suchang/Code/homework/math_search/math_back/static/book.gexf", "wb") as f:
        my_gexf.write(f)
