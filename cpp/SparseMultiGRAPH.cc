#ifndef SPARSEMULTIGRAPH_CC_
#define SPARSEMULTIGRAPH_CC_

#include <vector>
#include "Edge.cc"

using namespace std;

// Программа 17.9 (расширенная). Реализация АДТ графа (списки смежных вершин)
class SparseMultiGRAPH {
    int Vcnt, Ecnt;
    bool digraph;

    struct node {
        int v;
        node *next;
        node(int x, node *t) : v(x), next(t) {}
    };
    typedef node * link;
    vector<link> adj;

public:
    SparseMultiGRAPH(int V, bool digraph = false) :
        Vcnt(V), Ecnt(0), digraph(digraph), adj(V)
    {
        link t = 0;
        adj.assign(V, t);
    }

    // Упражнение 17.29
    SparseMultiGRAPH(const SparseMultiGRAPH &G) :
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

    void insert(Edge e) {
        int v = e.v, w = e.w;
        adj[v] = new node(w, adj[v]);
        if (!digraph && v != w) adj[w] = new node(v, adj[w]);
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

            if (!digraph && v != w) {
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

    void insert() {
        link t = 0;
        adj.push_back(t);
        ++Vcnt;
    }

    void remove(int v) {
        link t = adj[v], backup;
        while (t) {
            backup = t;
            t = t->next;
            delete backup;
            --Ecnt;
        }
        adj.erase(adj.begin() + v);
        --Vcnt;

        link *pt;
        for (int i = 0; i < Vcnt; ++i) {
            pt = &adj[i];
            while (*pt) {
                if ((*pt)->v == v) {
                    backup = (*pt)->next;
                    delete *pt;
                    *pt = backup;
                    if (digraph) --Ecnt;
                } else {
                    if ((*pt)->v > v) --(*pt)->v;
                    pt = &(*pt)->next;
                }
            }
        }
    }

    // Упражнение 17.34
    void removeLoopsAndParallels() {
        int *around = new int[Vcnt];
        int a;
        bool exist;

        for (int v = 0; v < Vcnt; ++v) {
            a = 0;
            link t = adj[v];
            while (t) {
                exist = false;
                for (int i = 0; i < a; ++i) {
                    if (around[i] == t->v) {
                        exist = true;
                        break;
                    }
                }

                if (exist) remove(Edge(v, t->v));
                else around[a++] = t->v;

                t = t->next;
            }

            remove(Edge(v, v));
        }

        delete [] around;
    }

    // Упражнение 17.43
    int degree(int v) {
        int n = 0;
        link t = adj[v];
        while (t) {
            t = t->next;
            ++n;
        }
        return n;
    }

    // Упражнение 17.44
    int zeros() const {
        int n = 0;
        for (int v = 0; v < Vcnt; ++v) {
            if (!adj[v]) ++n;
        }
        return n;
    }

    class adjIterator;
    friend class adjIterator;
};

// Программа 17.10. Итератор для представления графа в виде списка смежных вершин
class SparseMultiGRAPH::adjIterator {
    const SparseMultiGRAPH &G;
    int v;
    link t;

public:
    adjIterator(const SparseMultiGRAPH &G, int v) : G(G), v(v), t(0) {}

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
