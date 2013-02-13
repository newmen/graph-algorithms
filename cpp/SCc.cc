#ifndef SCC_CC_
#define SCC_CC_

#include <vector>
#include "clients.cc"
using namespace std;

// Программа 19.10. Сильные компоненты (алгоритм Косорайю)
template <class Graph>
class SCc {
    const Graph &G;
    int cnt, scnt;
    vector<int> postI, postR, id;

    void dfsR(const Graph &G, int w) {
        id[w] = scnt;
        typename Graph::adjIterator A(G, w);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (id[t] == -1) dfsR(G, t);
        }
        postI[cnt++] = w;
    }

public:
    SCc(const Graph &G) : G(G), cnt(0), scnt(0), postI(G.V()), postR(G.V()), id(G.V(), -1) {
        Graph R(G.V(), true);
        reverse<Graph, Graph>(G, R);
        for (int v = 0; v < R.V(); v++) {
            if (id[v] == -1) dfsR(R, v);
        }

        postR = postI;
        cnt = scnt = 0;
        id.assign(G.V(), -1);

        for (int v = G.V() - 1; v >= 0; v--) {
            if (id[postR[v]] == -1) {
                dfsR(G, postR[v]);
                scnt++;
            }
        }
    }

    int count() const { return scnt; }
    bool stronglyreachable(int v, int w) const { return id[v] == id[w]; }
    int ID(int v) const { return id[v]; }
};

#endif
