#ifndef DENSEGRAPH_H_
#define DENSEGRAPH_H_

#include <vector>
#include "Edge.cc"

using namespace std;

// Программа 17.7 (расширенная). Реализация АДТ графа (матрица смежности)
class DenseGRAPH {
    int Vcnt, Ecnt;
    bool digraph;
    vector< vector<bool> > adj;
    vector<int> deg; // Упражнение 17.42

public:
    DenseGRAPH(int V, bool digraph = false) :
        Vcnt(V), Ecnt(0), digraph(digraph), adj(V), deg(V, -1)
    {
        for (int i = 0; i < V; i++) adj[i].assign(V, false);
    }

    int V() const { return Vcnt; }
    int E() const { return Ecnt; }
    bool directed() const { return digraph; }
    
    void insert(Edge e) {
        int v = e.v, w = e.w;
        if (adj[v][w] == false) Ecnt++;
        adj[v][w] = true;
        if (!digraph) adj[w][v] = true;
    }
    
    void remove(Edge e) {
        int v = e.v, w = e.w;
        if (adj[v][w] == true) Ecnt--;
        adj[v][w] = false;
        if (!digraph) adj[w][v] = false;
    }

    bool edge(int v, int w) const {
        return adj[v][w];
    }

    // Упражнение 17.20
    void insert() {
        for (int v = 0; v < Vcnt; ++v) {
            adj[v].push_back(false);
        }
        adj.push_back(vector<bool>(++Vcnt, false));
        deg.push_back(-1);
    }
    void remove(int v) {
        vector< vector<bool> >::iterator row = adj.begin() + v;
        for (vector<bool>::const_iterator p = row->begin(); p != row->end(); ++p) {
            if (*p) --Ecnt;
        }
        adj.erase(row);

        for (row = adj.begin(); row != adj.end(); ++row) {
            vector<bool>::iterator p = row->begin() + v;
            row->erase(p);
        }
        --Vcnt;

        deg.erase(deg.begin() + v);
    }

    // Упражнение 17.34
    void removeLoopsAndParallels() {
        for (int v = 0; v < Vcnt; ++v) {
            if (adj[v][v]) --Ecnt;
            adj[v][v] = false;
        }
    }

    // Упражнение 17.42
    int degree(int v) {
        if (deg[v] == -1) {
            deg[v] = 0;
            for (int i = 0; i < Vcnt; ++i) {
                if (adj[v][i]) ++deg[v];
            }
        }
        return deg[v];
    }

    // Упражнение 17.44
    int zeros() const {
        int n = 0;
        bool bonded;
        for (int v = 0; v < Vcnt; ++v) {
            bonded = false;
            for (int w = 0; w < Vcnt; ++w) {
                if (!adj[v][w]) continue;
                bonded = true;
                break;
            }
            if (!bonded) ++n;
        }
        return n;
    }

    class adjIterator;
    friend class adjIterator;
};

// Программа 17.8. Итератор для представления матрицы смежности
class DenseGRAPH::adjIterator {
    const DenseGRAPH &G;
    int v, i;

public:
    adjIterator(const DenseGRAPH &G, int v) : G(G), v(v), i(-1) {}

    int beg() {
        i = -1;
        return nxt();
    }

    int nxt() {
        for (i++; i < G.V(); i++) {
            if (G.adj[v][i] == true) return i;
        }
        return -1;
    }

    bool end() {
        return i >= G.V();
    }
};

#endif
