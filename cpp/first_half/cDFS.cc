#ifndef CDFS_CC_
#define CDFS_CC_

#include <vector>

using namespace std;

// Программа 18.1. Поиск в глубину связной компоненты
template <class Graph>
class cDFS {
    const Graph &G;
    int cnt;
    vector<int> ord;

    void searchC(int v) {
        ord[v] = cnt++;
        typename Graph::adjIterator A(G, v);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (ord[t] == -1) searchC(t);
        }
    }

public:
    cDFS(const Graph &G, int v = 0) : G(G), ord(0), ord(G.V(), -1) {
        searchC(v);
    }

    int count() const { return cnt; }
    int operator [] (int v) const { return ord[v]; }
};

#endif
