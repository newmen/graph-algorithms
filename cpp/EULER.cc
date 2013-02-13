#ifndef EULER_CC_
#define EULER_CC_

#include <iostream>
#include "SEARCH.cc"

using namespace std;

// Программа 18.5. Двухпроходный эйлеров цикл
template <class Graph>
class EULER : public SEARCH<Graph> {
    void searchC(Edge e) {
        int v = e.v, w = e.w;
        this->ord[w] = this->cnt++;
        cout << "-" << w;
        
        typename Graph::adjIterator A(this->G, w);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (this->ord[t] == -1) searchC(Edge(w, t));
            else if (this->ord[t] < this->ord[v]) {
                cout << "-" << t << "-" << w;
            }
        }
        
        if (v != w) cout << "-" << v;
        else cout << endl;
    }

public:
    EULER(const Graph &G) : SEARCH<Graph>(G) {
        this->search();
    }

};

#endif