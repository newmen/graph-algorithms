#ifndef STLSPARSEMULTIGRAPH_CC_
#define STLSPARSEMULTIGRAPH_CC_

#include <algorithm>
#include <list>
#include <vector>
#include "Edge.cc"

using namespace std;

// Упражнение 17.30

class STLSparseMultiGRAPH {
    typedef list<int> Links;

public:
    class adjIterator;
    friend class adjIterator;

    STLSparseMultiGRAPH(int V, bool digraph = false) :
        Vcnt(V), Ecnt(0), digraph(digraph), adj(V) {}

    int V() const { return Vcnt; }
    int E() const { return Ecnt; }
    bool directed() const { return digraph; }

    void insert(Edge e) {
        int v = e.v, w = e.w;
        adj[v].push_back(w);
        if (!digraph && v != w) adj[w].push_back(v);
        ++Ecnt;
    }

    void remove(Edge e) {
        int v = e.v, w = e.w;
        Links::iterator p = find(adj[v].begin(), adj[v].end(), w);
        if (p != adj[v].end()) {
            adj[v].erase(p);

            if (!digraph && v != w) {
                p = find(adj[w].begin(), adj[w].end(), v);
                adj[w].erase(p);
            }

            --Ecnt;
        }
    }

    bool edge(int v, int w) const {
        return find(adj[v].begin(), adj[v].end(), w) != adj[v].end();
    }

    // Упражнение 17.34
    void removeLoopsAndParallels() {
        Links around;
        int exist;

        for (int v = 0; v < Vcnt; ++v) {
            around.clear();
            for (Links::const_iterator a = adj[v].begin(); a != adj[v].end(); ++a) {
                exist = -1;
                for (Links::const_iterator p = around.begin(); p != around.end(); ++p) {
                    if (*p == *a) {
                        exist = *p;
                        break;
                    }
                }

                if (exist == -1) around.push_back(*a);
                else remove(Edge(v, exist));
            }

            remove(Edge(v, v));
        }
    }

private:
    int Vcnt, Ecnt;
    bool digraph;
    vector<Links> adj;
};

class STLSparseMultiGRAPH::adjIterator {
    const STLSparseMultiGRAPH &G;
    int v;
    Links::const_iterator p;

public:
    adjIterator(const STLSparseMultiGRAPH &G, int v) : G(G), v(v) {}

    int beg() {
        p = G.adj[v].begin();
        return (p != G.adj[v].end()) ? *p : -1;
    }

    int nxt() {
        if (p != G.adj[v].end()) ++p;
        return (p != G.adj[v].end()) ? *p : -1;
    }

    bool end() {
        return p == G.adj[v].end();
    }
};

#endif
