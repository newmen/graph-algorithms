#ifndef SPATH_CC_
#define SPATH_CC_

#include <vector>

using namespace std;

// Программа 17.16. Поиск простого пути
template <class Graph>
class sPATH {
    const Graph &G;
    vector<bool> visited;
    bool found;

    bool searchR(int v, int w) {
        if (v == w) return true;
        visited[v] = true;
        typename Graph::adjIterator A(G, v);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (!visited[t] && searchR(t, w)) return true;
        }
        return false;
    }

public:
    sPATH(const Graph &G, int v, int w) : G(G), visited(G.V(), false) {
        found = searchR(v, w);
    }

    bool exist() const {
        return found;
    }
};

#endif