#ifndef DEGREE_CC_
#define DEGREE_CC_

#include <vector>

using namespace std;

// Программа 17.11. Реализация класса, определяющего степени вершин
template <class Graph>
class DEGREE {
    const Graph &G;
    vector<int> degree;

public:
    DEGREE(const Graph &G) : G(G), degree(G.V(), 0) {
        for (int v = 0; v < G.V(); v++) {
            typename Graph::adjIterator A(G, v);
            for (A.beg(); !A.end(); A.nxt()) ++degree[v];
        }
    }

    int operator [] (int v) const {
        return degree[v];
    }
};

#endif