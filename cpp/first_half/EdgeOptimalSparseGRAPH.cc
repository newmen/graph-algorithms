#ifndef EDGEOPTIMALSPARSEGRAPH_CC_
#define EDGEOPTIMALSPARSEGRAPH_CC_

#include <map>
#include <vector>
#include "Edge.cc"

using namespace std;

// Упражнение 17.46, 17.49

#define HASH_T int

class EdgeOptimalSparseGRAPH {
    struct node {
        int v;
        node *next, *prev;
        node(int x, node *t) : v(x), next(t), prev(0) {}
    };
    
    typedef node * link;

public:
    class adjIterator;
    friend class adjIterator;

    EdgeOptimalSparseGRAPH(int V, bool digraph = false) :
        Vcnt(V), Ecnt(0), digraph(digraph), adj(V)
    {
        link t = 0;
        adj.assign(V, t);
    }

    EdgeOptimalSparseGRAPH(const EdgeOptimalSparseGRAPH &G) :
        Vcnt(G.V()), Ecnt(G.E()), digraph(G.directed()), adj(G.V())
    {
        for (int i = 0; i < Vcnt; ++i) {
            link t = G.adj[i];
            while (t) {
                simpleInsert(i, t->v);
                t = t->next;
            }
        }
    }

    ~EdgeOptimalSparseGRAPH() {
        for (vector<link>::iterator p = adj.begin(); p != adj.end(); ++p) {
            link t = *p, pv;
            while (t) {
                pv = t;
                t = t->next;
                delete pv;
            }
        }
    }

    int V() const { return Vcnt; }
    int E() const { return Ecnt; }
    bool directed() const { return digraph; }

    void insert(Edge e) {
        int v = e.v, w = e.w;
        if (v == w || edge(v, w)) return;

        simpleInsert(v, w);
        if (!digraph) simpleInsert(w, v);
        
        ++Ecnt;
    }

    void remove(Edge e) {
        int v = e.v, w = e.w;
        if (!edge(v, w)) return;

        simpleRemove(v, w);
        if (!digraph) simpleRemove(w, v);

        --Ecnt;
    }

    bool edge(int v, int w) const {
        return edges.find(hashf(v, w)) != edges.end();
    }

    void insert() {
        link t = 0;
        adj.push_back(t);
        ++Vcnt;
    }

    // Упражнение 17.47
    void remove(int v) {
        link t = adj[v], backup;
        while (t) {
            edges.erase(edges.find(hashf(v, t->v)));
            backup = t;
            t = t->next;
            delete backup;
            --Ecnt;
        }
        adj.erase(adj.begin() + v);
        --Vcnt;

        link *pt;
        for (int a, i = 0; i < Vcnt; ++i) {
            a = (i < v) ? i : i + 1;
            pt = &adj[i];
            while (*pt) {
                if ((*pt)->v == v) {
                    edges.erase(edges.find(hashf(a, (*pt)->v)));
                    backup = (*pt)->next;
                    delete *pt;
                    *pt = backup;
                    if (digraph) --Ecnt;
                } else {
                    if (a != i || (*pt)->v > v) {
                        edges.erase(edges.find(hashf(a, (*pt)->v)));
                    }
                    if ((*pt)->v > v) {
                        --(*pt)->v;
                    }
                    if (a != i || (*pt)->v > v) {
                        edges[hashf(i, (*pt)->v)] = *pt;
                    }
                    pt = &(*pt)->next;
                }
            }
        }
    }

    void removeLoopsAndParallels() {}

private:
    void simpleInsert(int v, int w) {
        link pv = adj[v];
        adj[v] = new node(w, pv);
        if (pv) pv->prev = adj[v];
        edges[hashf(v, w)] = adj[v];
    }

    void simpleRemove(int v, int w) {
        map<HASH_T, link>::iterator pt = edges.find(hashf(v, w));
        link t = pt->second;
        if (t->prev) t->prev->next = t->next;
        if (t->next) t->next->prev = t->prev;
        if (!t->prev && !t->next) adj[v] = 0;
        delete t;
        edges.erase(pt);
    }

    HASH_T hashf(int v, int w) const {
        return (v << 19) | (w << 7);
    }

private:
    int Vcnt, Ecnt;
    bool digraph;
    vector<link> adj;
    map<HASH_T, link> edges;
};

class EdgeOptimalSparseGRAPH::adjIterator {
    const EdgeOptimalSparseGRAPH &G;
    int v;
    link t;

public:
    adjIterator(const EdgeOptimalSparseGRAPH &G, int v) : G(G), v(v), t(0) {}

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
