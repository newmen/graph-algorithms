#ifndef MSTBR_CC_
#define MSTBR_CC_

#include <vector>
#include "clients.cc"
using namespace std;

// Программа 20.9. Алгоритм Борувки построения дерева MST
template <class Graph, class Edge>
class MSTbr {
    const Graph &G;
    vector<Edge *> a, b, mst;
    UF uf;

public:
    MSTbr(const Graph &G) : G(G), mst(G.V()), uf(G.V()) {
        a = edges<Graph, Edge>(G);
        int N = -1, k = 0;
        for (int E = a.size(); E != 0; E = N) {
            int h, i, j;
            b.assign(G.V(), (Edge *)0);
            for (h = 0, N = 0; h < E; h++) {
                Edge *e = a[h];
                i = uf.find(e->v()), j = uf.find(e->w());
                if (i == j) continue;
                if (!b[i] || e->wt() < b[i]->wt()) b[i] = e;
                if (!b[j] || e->wt() < b[j]->wt()) b[j] = e;
                a[N++] = e;
            }
            for (h = 0; h < G.V(); h++) {
                if (b[h] && !uf.find(i = b[h]->v(), j = b[h]->w())) {
                    uf.unite(i, j);
                    mst[k++] = b[h];
                }
            }
        }
    }

    void show() {
        for (int v = 0; v < G.V(); ++v) {
            if (mst[v]) mst[v]->show();
        }
    }
};

#endif
