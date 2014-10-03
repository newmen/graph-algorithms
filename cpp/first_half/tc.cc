#ifndef TC_DFS_CC_
#define TC_DFS_CC_

#include "Edge.cc"

// Программа 19.4. Транзитивное замыкание, построенное на основе поиска в глубину
template <class Graph>
class tc {
    const Graph &G;
    Graph T;

    void tcR(int v, int w) {
        T.insert(Edge(v, w));
        typename Graph::adjIterator A(G, w);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (!T.edge(v, t)) tcR(v, t);
        }
    }

public:
    tc(const Graph &G) : G(G), T(G.V(), true) {
        for (int v = 0; v < G.V(); ++v) tcR(v, v);
    }

    bool reachable(int s, int t) const {
        return T.edge(s, t);
    }
};

#endif