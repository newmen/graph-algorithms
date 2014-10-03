#ifndef GPATH_CC_
#define GPATH_CC_

#include <vector>

using namespace std;

// Программа 17.17. Гамильтонов путь
template <class Graph>
class gPATH {
    const Graph &G;
    vector<bool> visited;
    bool found;

    bool searchR(int v, int w, int d) {
        if (v == w) return d == 0;
        visited[v] = true;
        typename Graph::adjIterator A(G, v);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (!visited[t] && searchR(t, w, d - 1)) return true;
        }
        visited[v] = false;
        return false;
    }

public:
    gPATH(const Graph &G, int v, int w) : G(G), visited(G.V(), false) {
        found = searchR(v, w, G.V() - 1);
    }

    bool exist() const {
        return found;
    }
};

#endif