#ifndef BI_CC
#define BI_CC

#include <vector>
using namespace std;

// Программа 18.6. Раскраска графа в два цвета (двудольные графы)
template <class Graph>
class BI {
    const Graph &G;
    bool OK;
    vector<int> vc;

    bool dfsR(int v, int c) {
        vc[v] = (c + 1) % 2;
        typename Graph::adjIterator A(G, v);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (vc[t] == -1) {
                if (!dfsR(t, vc[v])) return false;
            } else {
                if (vc[t] != c) return false;
            }
        }

        return true;
    }

public:
    BI(const Graph &G) : G(G), OK(true), vc(G.V(), -1) {
        for (int v = 0; v < G.V(); v++) {
            if (vc[v] == -1) {
                if (!dfsR(v, 0)) {
                    OK = false;
                    return;
                }
            }
        }
    }

    bool bipartite() const { return OK; }
    int color(int v) const { return vc[v]; }
};

#endif
