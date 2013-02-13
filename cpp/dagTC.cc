#ifndef DAGTC_CC_
#define DAGTC_CC_

#include <vector>
#include "Edge.cc"
using namespace std;

// Программа 19.9. Транзитивное замыкание графа DAG
template <class tcDag, class Dag>
class dagTC {
    const Dag &D;
    tcDag T;
    int cnt;
    vector<int> pre;

    void tcR(int w) {
        pre[w] = cnt++;
        typename Dag::adjIterator A(D, w);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            T.insert(Edge(w, t));
            if (pre[t] > pre[w]) continue;
            if (pre[t] == -1) tcR(t);
            for (int i = 0; i < T.V(); i++) {
                if (T.edge(t, i)) T.insert(Edge(w, i));
            }
        }
    }

public:
    dagTC(const Dag &D) : D(D), T(D.V(), true), cnt(0), pre(D.V(), -1) {
        for (int v = 0; v < D.V(); v++) {
            if (pre[v] == -1) tcR(v);
        }
    }

    bool reahable(int v, int w) const { return T.edge(v, w); }
};

#endif