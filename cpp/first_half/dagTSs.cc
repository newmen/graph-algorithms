#ifndef DAGTSS_CC_
#define DAGTSS_CC_

#include <vector>
using namespace std;

// Программа 19.6. Обратная топологическая сортировка
template <class Dag>
class dagTSs {
    const Dag &D;
    int cnt, tcnt;
    vector<int> pre, post, postI;

    void tsR(int v) {
        pre[v] = cnt++;
        typename Dag::adjIterator A(D, v);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (pre[v] == -1) tsR(t);
        }
        post[v] = tcnt;
        postI[tcnt++] = v;
    }

public:
    dagTSs(const Dag &D) : D(D), cnt(0), tcnt(0),
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