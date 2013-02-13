#ifndef SPARSEGRAPH_CC_
#define SPARSEGRAPH_CC_

#include <vector>
#include "Edge.cc"

using namespace std;

// Упражнение 17.35
class SparseGRAPH {
    struct node {
        int v;
        node *next;
        node(int x, node *t) : v(x), next(t) {}
    };

    typedef node * link;

public:
    class adjIterator;
    friend class adjIterator;

    SparseGRAPH(int V, bool digraph = false) :
        Vcnt(V), Ecnt(0), digraph(digraph), adj(V)
    {
        link t = 0;
        adj.assign(V, t);
    }

    // Упражнение 17.29
    SparseGRAPH(const SparseGRAPH &G) :
        Vcnt(G.V()), Ecnt(G.E()), digraph(G.directed()), adj(G.V())
    {
        for (int i = 0; i < Vcnt; ++i) {
            link t = G.adj[i];
            while (t) {
                adj[i] = new node(t->v, adj[i]);
                t = t->next;
            }
        }
    }

    ~SparseGRAPH() {
        for (vector<link>::iterator p = adj.begin(); p != adj.end(); ++p) {
            link t = *p, prev;
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

    void insert(Edge e) {
        int v = e.v, w = e.w;
        if (v == w || edge(v, w)) return;

        adj[v] = new node(w, adj[v]);
        if (!digraph) adj[w] = new node(v, adj[w]);
        ++Ecnt;
    }

    // Упражнение 17.28
    void remove(Edge e) {
        int v = e.v, w = e.w;
        link *t = &adj[v];
        while (*t && (*t)->v != w) {
            t = &(*t)->next;
        }
        if (*t) {
            link nxt = (*t)->next;
            delete *t;
            *t = nxt;

            if (!digraph) {
                t = &adj[w];
                while ((*t)->v != v) {
                    t = &(*t)->next;
                }
                nxt = (*t)->next;
                delete *t;
                *t = nxt;
            }

            --Ecnt;
        }
    }
    bool edge(int v, int w) const {
        link t = adj[v];
        while (t && t->v != w) t = t->next;
        return t;
    }

    // Упражнение 17.34
    void removeLoopsAndParallels() {}

private:
    int Vcnt, Ecnt;
    bool digraph;
    vector<link> adj;
};

class SparseGRAPH::adjIterator {
    const SparseGRAPH &G;
    int v;
    link t;

public:
    adjIterator(const SparseGRAPH &G, int v) : G(G), v(v), t(0) {}

    int beg() {
        t = G.adj[v];
        return t ? t->v : -1;
    }

    int nxt() {
        if (t) t = t->next;
        return t ? t->v : -1;
    }

    bool end() {
        return t == 0;
    }
};

#endif
