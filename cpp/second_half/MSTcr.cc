#ifndef MSTCR_CC_
#define MSTCR_CC_

#include <algorithm>
#include <vector>
#include "clients.cc"
#include "UF.cc"

// Программа 20.8 (обновлённая). Алгоритм Крускала, обеспечивающий построение дерева MST
template <class Graph, class Edge>
class MSTcr {
    const Graph &G;
    vector<Edge *> a, mst;
    UF uf;

    struct Compare {
        bool operator() (const Edge *a, const Edge *b) {
            return a->wt() < b->wt();
        }
    };

public:
    MSTcr(const Graph &G) : G(G), mst(G.V()), uf(G.V()) {
        int V = G.V(), E = G.E();
        a = edges<Graph, Edge>(G);
        sort(a.begin(), a.end(), Compare());
        for (int i = 0, k = 1; i < E && k < V; i++) {
            if (!uf.find(a[i]->v(), a[i]->w())) {
                uf.unite(a[i]->v(), a[i]->w());
                mst[k++] = a[i];
            }
        }
    }

    void show() {
        for (int v = 1; v < G.V(); ++v) {
            if (mst[v]) mst[v]->show();
        }
    }
};

#endif