#ifndef EPATH_CC_
#define EPATH_CC_

#include <iostream>
#include <stack>
#include "DEGREE.cc"
#include "Edge.cc"

using namespace std;

// Программа 17.18. Существование эйлерова цикла
template <class Graph>
class ePATH {
    Graph G;
    int v, w;
    bool found;
    stack<int> S;
    
    int tour(int v);

public:
    ePATH(const Graph &G, int v, int w) : G(G), v(v), w(w) {
        DEGREE<Graph> deg(G);
        int t = deg[v] + deg[w];
        if (t % 2 != 0) {
            found = false;
            return;
        }

        for (t = 0; t < G.V(); t++) {
            if (t != v && t != w && deg[t] % 2 != 0) {
                found = false;
                return;
            }
        }

        found = true;
    }

    bool exist() const {
        return found;
    }

    void show();
};

// Программа 17.19 (обновлённая). Поиск эйлерова пути с линейным временем выполнения
template <class Graph>
int ePATH<Graph>::tour(int v) {
    while (true) {
        typename Graph::adjIterator A(G, v);
        int t = A.beg();
        if (A.end()) break;

        S.push(v);
        G.remove(Edge(v, t));
        v = t;
    }
    return v;
}
template <class Graph>
void ePATH<Graph>::show() {
    if (!found) return;
    cout << v;
    while (tour(v) == v && !S.empty()) {
        v = S.top();
        S.pop();
        cout << "-" << v;
    }
    cout << endl;
}

#endif