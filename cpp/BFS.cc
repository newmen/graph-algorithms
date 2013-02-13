#ifndef BFS_CC_
#define BFS_CC_

#include <queue>
#include "SEARCH.cc"
using namespace std;

// Упражнение 18.52
template <class Graph>
class BFS : public SEARCH<Graph> {
    vector<int> st;

    // Программа 18.8. Поиск в ширину
    void notOptimal(Edge e) {
        queue<Edge> Q;
        Q.push(e);
        while (!Q.empty()) {
            e = Q.front();
            Q.pop();
            if (this->ord[e.w] == -1) {
                int v = e.v, w = e.w;
                this->ord[w] = this->cnt++;
                st[w] = v;
                typename Graph::adjIterator A(this->G, w);
                for (int t = A.beg(); !A.end(); t = A.nxt()) {
                    if (this->ord[t] == -1) Q.push(Edge(w, t));
                }
            }
        }
    }

    // Программа 18.9. Усовершенствованный алгоритм BFS
    void optimal(Edge e) {
        queue<Edge> Q;
        Q.push(e);
        this->ord[e.w] = this->cnt++;
        while (!Q.empty()) {
            e = Q.front();
            Q.pop();
            st[e.w] = e.v;
            typename Graph::adjIterator A(this->G, e.w);
            for (int t = A.beg(); !A.end(); t = A.nxt()) {
                if (this->ord[t] == -1) {
                    Q.push(Edge(e.w, t));
                    this->ord[t] = this->cnt++;
                }
            }
        }
    }

    void searchC(Edge e) {
        // notOptimal(e);
        optimal(e);
    }

public:
    BFS(const Graph &G) : SEARCH<Graph>(G), st(G.V(), -1) {
        this->search();
    }

    int ST(int v) const { return st[v]; }
};

#endif