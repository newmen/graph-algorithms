#ifndef DENSEGRAPH_CC_
#define DENSEGRAPH_CC_

#include <vector>
using namespace std;

// Программа 20.3 (обновлённая). Класс взвешенного графа (представление в виде матрицы смежности)
template <class Edge>
class DenseGRAPH {
    int Vcnt, Ecnt;
    bool digraph;
    vector< vector<Edge *> > adj;

public:
    DenseGRAPH(int V, bool digraph = false) : adj(V), Vcnt(V), Ecnt(0), digraph(digraph) {
        for (int i = 0; i < V; i++) {
            adj[i].assign(V, (Edge *)0);
        }
    }

    ~DenseGRAPH() {
        for (int v = 0; v < Vcnt; v++) {
            for (int w = 0; w < Vcnt; w++) {
                if (adj[v][w]) {
                    delete adj[v][w];
                    // adj[v][w] = 0;
                    if (!digraph) adj[w][v] = 0;
                }
            }
        }
    }

    int V() const { return Vcnt; }
    int E() const { return Ecnt; }
    bool directed() const { return digraph; }

    void insert(Edge *e) {
        int v = e->v(), w = e->w();
        if (adj[v][w] == 0) Ecnt++;
        adj[v][w] = e;
        if (!digraph) adj[w][v] = e;
    }

    void remove(Edge *e) {
        int v = e->v(), w = e->w();
        if (adj[v][w] != 0) {
            delete adj[v][w];
            Ecnt--;
        }
        adj[v][w] = 0;
        if (!digraph) {
            if (adj[w][v]) delete adj[w][v];
            adj[w][v] = 0;
        }
    }

    Edge *edge(int v, int w) const {
        return adj[v][w];
    }

    class adjIterator;
    friend class adjIterator;
};

// Программа 20.4. Класс итератора, ориентированный на представление графа в виде матрицы смежности
template <class Edge>
class DenseGRAPH<Edge>::adjIterator {
    const DenseGRAPH<Edge> &G;
    int i, v;

public:
    adjIterator(const DenseGRAPH<Edge> &G, int v) : G(G), v(v), i(0) {}

    Edge *beg() {
        i = -1;
        return nxt();
    }

    Edge *nxt() {
        for (i++; i < G.V(); i++) {
            if (G.edge(v, i)) return G.adj[v][i];
        }
        return 0;
    }

    bool end() const {
        return i >= G.V();
    }
};

#endif
