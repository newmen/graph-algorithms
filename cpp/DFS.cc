#ifndef DFS_CC_
#define DFS_CC_

#include "SEARCH.cc"

// Программа 18.3. Производный класс поиска в глубину
template <class Graph>
class DFS : public SEARCH<Graph> {
    vector<int> st;

protected:
    void searchC(Edge e) {
        int w = e.w;
        this->ord[w] = this->cnt++;
        st[e.w] = e.v;
        typename Graph::adjIterator A(this->G, w);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (this->ord[t] == -1) searchC(Edge(w, t));
        }
    }

public:
    DFS(const Graph &G) : SEARCH<Graph>(G), st(G.V(), -1) {
        this->search();
    }

    int ST(int v) const { return st[v]; }
};

#endif
