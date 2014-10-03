#ifndef SCG_CC_
#define SCG_CC_

#include <stack>
#include <vector>
using namespace std;

// Программа 19.12. Сильные компоненты (алгоритм Габова)
template <class Graph>
class SCg {
    const Graph &G;
    stack<int> S, path;
    int cnt, scnt;
    vector<int> pre, id;

    void scR(int w) {
        pre[w] = cnt++;
        S.push(w);
        path.push(w);

        typename Graph::adjIterator A(G, w);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (pre[t] == -1) scR(t);
            else if (id[t] == -1) {
                while (pre[path.top()] > pre[t]) path.pop();
            }
        }

        if (path.top() == w) path.pop();
        else return;

        int v;
        do {
            v = S.top();
            S.pop();
            id[v] = scnt;
        } while (v != w);
        scnt++;
    }

public:
    SCg(const Graph &G) : G(G), cnt(0), scnt(0), pre(G.V(), -1), id(G.V(), -1) {
        for (int v = 0; v < G.V(); v++) {
            if (pre[v] == -1) scR(v);
        }
    }

    int count() const { return scnt; }
    bool stronglyreachable(int v, int w) const { return id[v] == id[w]; }
    int ID(int v) const { return id[v]; }
};

#endif
