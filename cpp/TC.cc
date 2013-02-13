#ifndef TC_CC_
#define TC_CC_

#include "Edge.cc"

// Программа 19.3. Алгоритм Уоршала
template <class tcGraph, class Graph>
class TC {
    tcGraph T;

public:
    TC(const Graph &G) : T(G) {
        for (int s = 0; s < T.V(); s++) T.insert(Edge(s, s));
        for (int i = 0; i < T.V(); i++) {
            for (int s = 0; s < T.V(); s++) {
                if (!T.edge(s, i)) continue;
                for (int t = 0; t < T.V(); t++) {
                    if (T.edge(t, i)) T.insert(Edge(s, t));
                }
            }
        }
    }

    bool reachable(int s, int t) const {
        return T.edge(s, t);
    }
};

#endif