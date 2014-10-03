#ifndef DENSEMULTIGRAPH_H_
#define DENSEMULTIGRAPH_H_

#include <vector>
#include "Edge.cc"

using namespace std;

// Упражнение 17.39
class DenseMultiGRAPH {
public:
    class adjIterator;
    friend class adjIterator;

    DenseMultiGRAPH(int V, bool digraph = false) :
        Vcnt(V), Ecnt(0), digraph(digraph), adj(V)
    {
        for (int i = 0; i < V; i++) adj[i].assign(V, 0);
    }

    int V() const { return Vcnt; }
    int E() const { return Ecnt; }
    bool directed() const { return digraph; }
    
    void insert(Edge e) {
        int v = e.v, w = e.w;
        ++adj[v][w];
        if (!digraph && v != w) ++adj[w][v];
        ++Ecnt;
    }
    
    void remove(Edge e) {
        int v = e.v, w = e.w;
        if (adj[v][w] > 0) {
            --adj[v][w];
            if (!digraph && v != w) --adj[w][v];
            --Ecnt;
        }
    }

    bool edge(int v, int w) const {
        return adj[v][w];
    }

    void insert() {
        for (vector< vector<int> >::iterator p = adj.begin(); p != adj.end(); ++p) {
            p->push_back(0);
        }
        adj.push_back(vector<int>(++Vcnt, 0));
    }

    void remove(int v) {
        vector< vector<int> >::iterator row = adj.begin() + v;
        for (vector<int>::const_iterator p = row->begin(); p != row->end(); ++p) {
            Ecnt -= *p;
        }
        adj.erase(row);

        for (row = adj.begin(); row != adj.end(); ++row) {
            vector<int>::iterator p = row->begin() + v;
            row->erase(p);
        }
        --Vcnt;
    }

    void removeLoopsAndParallels() {
        for (int v = 0; v < Vcnt; ++v) {
            Ecnt -= adj[v][v];
            adj[v][v] = 0;

            for (int w = 0; w < Vcnt; ++w) {
                if (adj[v][w] < 2) continue;
                remove(Edge(v, w));
            }
        }
    }

private:
    int Vcnt, Ecnt;
    bool digraph;
    vector< vector<int> > adj;
};

class DenseMultiGRAPH::adjIterator {
public:
    adjIterator(const DenseMultiGRAPH &G, int v) : G(G), v(v), i(0), inner(0) {}

    int beg() {
        i = 0;
        inner = 0;
        return nxt();
    }

    int nxt() {
        if (i < G.V() && inner++ < G.adj[v][i]) {
            return i;
        } else {
            for (++i; i < G.V(); ++i) {
                if (G.adj[v][i] == 0) continue;
                inner = 1;
                return i;
            }
            return -1;
        }
    }

    bool end() {
        return i >= G.V();
    }

private:
    const DenseMultiGRAPH &G;
    int v, i, inner;
};

#endif
