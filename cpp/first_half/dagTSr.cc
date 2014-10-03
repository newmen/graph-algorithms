#ifndef DAGTSR_CC_
#define DAGTSR_CC_

#include <vector>
using namespace std;

// Программа 19.7. Топологическая сортировка
template <class Dag>
class dagTSr {
    const Dag &D;
    int cnt, tcnt;
    vector<int> pre, post, postI;

    void tsR(int v) {
        pre[v] = cnt++;

        for (int w = 0; w < D.V(); w++) {
            if (D.edge(w, v) && pre[w] == -1) tsR(w);
        }

        post[v] = tcnt;
        postI[tcnt++] = v;
    }

public:
    dagTSr(const Dag &D) : D(D), cnt(0), tcnt(0),
        pre(D.V(), -1), post(D.V(), -1), postI(D.V(), -1)
    {
        for (int v = 0; v < D.V(); v++) {
            if (pre[v] == -1) tsR(v);
        }
    }

    int operator [] (int v) const { return postI[v]; }
    int relabel(int v) const { return post[v]; }
};

#endif