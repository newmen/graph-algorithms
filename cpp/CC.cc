#ifndef CC_CC_
#define CC_CC_

#include <vector>

using namespace std;

// Программа 17.5, 18.4. Интерфейс связности, Связность графа
template <class Graph>
class CC {
    const Graph &G;
    int ccnt;
    vector<int> id;

    void ccR(int w) {
        id[w] = ccnt;
        typename Graph::adjIterator A(G, w);
        for (int v = A.beg(); !A.end(); v = A.nxt()) {
            if (id[v] == -1) ccR(v);
        }
    }

public:
    CC(const Graph &) : G(G), ccnt(0), id(G.V(), -1) {
        for (int v = 0; v < G.V(); v++) {
            if (id[v] == -1) {
                ccR(v);
                ccnt++;
            }
        }
    }

    int count() const { return ccnt; }
    bool connect(int s, int t) { return id[s] == id[t]; }
};

#endif
