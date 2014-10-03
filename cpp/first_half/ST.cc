#ifndef ST_CC_
#define ST_CC_

#include <string>

using namespace std;

// Программа 17.15. Символьная индексация имён вершин
class ST {
    struct node {
        int v, d;
        node *l, *m, *r;
        node(int d) : v(-1), d(d), l(0), m(0), r(0) {}
    };

    typedef node * link;

    int N, val;
    link head;

    link indexR(link h, const string &s, int w) {
        int i = s[w];
        if (h == 0) h = new node(i);
        if (i == 0) {
            if (h->v == -1) h->v = N++;
            val = h->v;
            return h;
        }
        if (i < h->d) h->l = indexR(h->l, s, w);
        else if (i == h->d) h->m = indexR(h->m, s, w + 1);
        else if (i > h->d) h->r = indexR(h->r, s, w);
        return h;
    }

    void clearMemory(link h) {
        if (!h) return;
        if (h->l) clearMemory(h->l);
        if (h->m) clearMemory(h->m);
        if (h->r) clearMemory(h->r);
        delete h;
    }

public:
    ST() : N(0), head(0) {}
    ~ST() {
        clearMemory(head);
    }

    int index(const string &key) {
        head = indexR(head, key, 0);
        return val;
    }
};

#endif