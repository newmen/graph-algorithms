#ifndef EDGE_CC_
#define EDGE_CC_

// Программа 17.1. Интерфейс ребра графа
struct Edge {
    int v, w;
    Edge(int v = -1, int w = -1) : v(v), w(w) {}
};

#endif