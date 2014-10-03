#ifndef UNDIRBITDENSEGRAPH_H_
#define UNDIRBITDENSEGRAPH_H_

#include "Edge.cc"

using namespace std;

// Упражнение 17.23

class UndirBitDenseGRAPH {
public:
    class adjIterator;
    friend class adjIterator;

    UndirBitDenseGRAPH(int V) : Vcnt(V), Ecnt(0) {
        int N = countUp(1);
        allocMem(N);
    }
    
    UndirBitDenseGRAPH(const UndirBitDenseGRAPH &G) : Vcnt(G.V()), Ecnt(G.E()) {
        int N = countUp(1);
        int allocated = N / bitsize();
        if (N % bitsize() > 0) ++allocated;
        adj = new int[allocated];
        for (int i = 0; i < allocated; i++) adj[i] = G.adj[i];
    }

    ~UndirBitDenseGRAPH() {
        delete [] adj;
    }

    int V() const { return Vcnt; }
    int E() const { return Ecnt; }
    bool directed() const { return false; }
    
    void insert(Edge e) {
        if (!edge(e.v, e.w)) ++Ecnt;
        setEdge(e.v, e.w, 1);
    }
    
    void remove(Edge e) {
        if (edge(e.v, e.w)) --Ecnt;
        setEdge(e.v, e.w, 0);
    }

    bool edge(int v, int w) const {
        int i, seek;
        setupCarrete(i, seek, v, w);
        return adj[i] & (1 << seek);
    }

    void insert() {
        int newElementsNum = countUp(1, Vcnt + 1);
        int *fatArj = new int[newElementsNum];
        for (int k = 0; k < newElementsNum; k++) {
            fatArj[k] = 0;
        }

        int i = -1;
        for (int v = 0; v < Vcnt; ++v) {
            for (int w = v; w < Vcnt + 1; ++w) {
                ++i;
                if (w == Vcnt) continue;
                fatArj[i] = edge(v, w);
            }
        }

        delete [] adj;
        allocMem(newElementsNum);
        ++Vcnt;

        fillFromFat(fatArj);
        delete [] fatArj;
    }

    void remove(int v) {
        for (int i = 0; i < Vcnt; ++i) {
            if (edge(v, i)) --Ecnt;
        }

        int newElementsNum = countUp(1, Vcnt - 1);
        int *fatArj = new int[newElementsNum];
        int i = 0;
        for (int u = 0; u < Vcnt; ++u) {
            if (u == v) continue;
            for (int w = u; w < Vcnt; ++w) {
                if (v >= u && (w - u) == (u - v)) continue;
                fatArj[i++] = edge(u, w);
            }
        }

        delete [] adj;
        allocMem(newElementsNum);
        --Vcnt;

        fillFromFat(fatArj);
        delete [] fatArj;
    }

    // Упражнение 17.34
    void removeLoopsAndParallels() {
        for (int v = 0; v < Vcnt; ++v) remove(Edge(v, v));
    }

private:
    void setEdge(int v, int w, int value) {
        int i, seek;
        setupCarrete(i, seek, v, w);
        if (value == 0) {
            adj[i] ^= (1 << seek);
        } else {
            adj[i] |= (1 << seek);
        }
    }

    int bitsize() const {
        return (int)sizeof(int);
    }

    void allocMem(int N) {
        int allocated = N / bitsize();
        if (N % bitsize() > 0) ++allocated;
        adj = new int[allocated];
        for (int i = 0; i < allocated; i++) adj[i] = 0;
    }

    // arithmetic progression
    int countUp(int initialValue, int V = -1) const {
        if (V == -1) V = Vcnt;
        return (int)((V - initialValue + 1) * (initialValue + V) * 0.5);
    }

    void setupCarrete(int &i, int &seek, int v, int w) const {
        int _v, _w;
        if (v < w) {
            _v = v;
            _w = w;
        } else {
            _v = w;
            _w = v;
        }

        int before = (_v > 0) ? countUp(Vcnt - _v + 1) : 0;
        int currElement = before + _w - _v;

        i = currElement / bitsize();
        seek = bitsize() - currElement % bitsize() - 1;
    }

    void fillFromFat(int *fatArj) {
        int i = 0;
        for (int v = 0; v < Vcnt; ++v) {
            for (int w = v; w < Vcnt; ++w) {
                setEdge(v, w, fatArj[i++]);
            }
        }
    }

private:
    int Vcnt, Ecnt;
    int *adj;
};

class UndirBitDenseGRAPH::adjIterator {
public:
    adjIterator(const UndirBitDenseGRAPH &G, int v) : G(G), v(v), i(-1) {}

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
    const UndirBitDenseGRAPH &G;
    int v, i;
};

#endif
