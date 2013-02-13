#ifndef PFS_CC_
#define PFS_CC_

#include "SEARCH.cc"
#include "GQ.cc"

// Программа 18.10. Обобщённый поиск на графе
template <class Graph>
class PFS : public SEARCH<Graph> {
    vector<int> st;

    void searchC(Edge e) {
        GQ<Edge> Q(this->G.V());
        Q.put(e);
        this->ord[e.w] = this->cnt++;
        while (!Q.empty()) {
            e = Q.get();
            st[e.w] = e.v;
            typename Graph::adjIterator A(this->G, e.w);
            for (int t = A.beg(); !A.end(); t = A.nxt()) {
                if (this->ord[t] == -1) {
                    Q.put(Edge(e.w, t));
                    this->ord[t] = this->cnt++;
                } else if (st[t] == -1) {
                    Q.update(Edge(e.w, t));
                }
            }
        }
    }

public:
    PFS(const Graph &G) : SEARCH<Graph>(G), st(G.V(), -1) {
        this->search();
    }

    int ST(int v) const { return st[v]; }
};

#endif