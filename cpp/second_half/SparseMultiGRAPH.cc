#ifndef SPARSEMULTIGRAPH_CC_
#define SPARSEMULTIGRAPH_CC_

#include <vector>

// Программа 20.5. Класс взвешенного графа (списки смежных вершин)
template <class Edge>
class SparseMultiGRAPH {
    int Vcnt, Ecnt;
    bool digraph;
    struct node {
        Edge *e;
        node *next;
        node(Edge *e, node *next) : e(e), next(next) {}
    };
    typedef node * link;
    vector<link> adj;

public:
    SparseMultiGRAPH(int V, bool digraph = false) :
        adj(V), Vcnt(V), Ecnt(0), digraph(digraph) {}
    ~SparseMultiGRAPH() {
        for (int v = 0; v < Vcnt; ++v) {
            link t = adj[v], prev;
            while (t) {
                prev = t;
                t = t->next;
                delete prev;
            }
        }
    }

    int V() const { return Vcnt; }
    int E() const { return Ecnt; }
    bool directed() const { return digraph; }

    void insert(Edge *e) {
        adj[e->v()] = new node(e, adj[e->v()]);
        if (!digraph) {
            adj[e->w()] = new node(e, adj[e->w()]);
        }
        Ecnt++;
    }

    class adjIterator;
    friend class adjIterator;
};

#endif
