#ifndef UNDIRDENSEGRAPH_H_
#define UNDIRDENSEGRAPH_H_

#include <vector>
#include "Edge.cc"

using namespace std;

// Упражнение 17.22

class UndirDenseGRAPH {
public:
    class adjIterator;
    friend class adjIterator;

    UndirDenseGRAPH(int V) : Vcnt(V), Ecnt(0), adj(V) {
        for (int i = 0; i < V; i++) adj[i].assign(V - i, false);
    }

    int V() const { return Vcnt; }
    int E() const { return Ecnt; }
    bool directed() const { return false; }
    
    void insert(Edge e) {
        if (!edge(e.v, e.w)) ++Ecnt;
        setEdge(e, true);
    }
    
    void remove(Edge e) {
        if (edge(e.v, e.w)) --Ecnt;
        setEdge(e, false);
    }

    bool edge(int v, int w) const {
        int _v, _w;
        if (v < w) {
            _v = v;
            _w = w;
        } else {
            _v = w;
            _w = v;
        }
        return adj[_v][_w - _v];
    }

    void insert() {
        for (vector< vector<bool> >::iterator p = adj.begin(); p != adj.end(); ++p) {
            p->push_back(false);
        }
        adj.push_back(vector<bool>(1, false));
        ++Vcnt;
    }

    void remove(int v) {
        for (int i = 0; i < Vcnt; ++i) {
            if (edge(v, i)) --Ecnt;
        }
        adj.erase(adj.begin() + v);

        for (int i = 0; i < v; ++i) {
            vector<bool>::iterator p = adj[i].begin() + (v - i);
            adj[i].erase(p);
        }
        --Vcnt;
    }

    // Упражнение 17.34
    void removeLoopsAndParallels() {
        for (int v = 0; v < Vcnt; ++v) {
            if (adj[v][0]) --Ecnt;
            adj[v][0] = false;
        }
    }

private:
    void setEdge(const Edge &e, bool value) {
        int v, w;
        if (e.v < e.w) {
            v = e.v;
            w = e.w;
        } else {
            v = e.w;
            w = e.v;
        }
        adj[v][w - v] = value;
    }

private:
    int Vcnt, Ecnt;
    vector< vector<bool> > adj;

};

class UndirDenseGRAPH::adjIterator {
public:
    adjIterator(const UndirDenseGRAPH &G, int v) : G(G), v(v), i(-1) {}

    int beg() {
        i = -1;
        return nxt();
    }

    int nxt() {
        for (i++; i < G.V(); i++) {
            if (G.edge(v, i)) return i;
        }
        return -1;
    }

    bool end() {
        return i >= G.V();
    }

private:
    const UndirDenseGRAPH &G;
    int v, i;
};

#endif
