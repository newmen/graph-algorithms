#ifndef EC_CC_
#define EC_CC_

#include "SEARCH.cc"

// Программа 18.7. Ребёрная связность
template <class Graph>
class EC : public SEARCH<Graph> {
    int bcnt;
    vector<int> low;

    void searchR(Edge e) {
        int w = e.w;
        this->ord[w] = this->cnt++;
        low[w] = this->ord[w];

        typename Graph::adjIterator A(this->G, w);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (this->ord[t] == -1) {
                searchR(Edge(w, t));
                if (low[w] > low[t]) low[w] = low[t];
                if (low[t] == this->ord[t]) bcnt++; // новый мост
            } else if (t != e.v) {
                if (low[w] > this->ord[t]) low[w] = this->ord[t];
            }
        }
    }

public:
    EC(const Graph &G) : SEARCH<Graph>(G), bcnt(0), low(G.V(), -1) {
        this->search();
    }

    int count() const { return bcnt + 1; }
};

#endif
