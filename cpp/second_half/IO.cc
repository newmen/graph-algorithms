#ifndef IO_CC_
#define IO_CC_

#include <iostream>
#include "clients.cc"
#include "../first_half/ST.cc"

// Упражнение 20.9
template <class Graph, class Edge>
class IO {
public:
    static void show(const Graph &G);
    static void showEdges(const Graph &G);
    static void showAdj(const Graph &G);

    static void scanEZ(Graph &G);
    static void scan(Graph &G);

private:
    static bool isTerminateInput(int deep = 2);
};

template <class Graph, class Edge>
void IO<Graph, Edge>::show(const Graph &G) {
    for (int s = 0; s < G.V(); s++) {
        cout.width(2);
        cout << s << ": ";
        typename Graph::adjIterator A(G, s);
        for (Edge *e = A.beg(); !A.end(); e = A.nxt()) {
            cout.width(2);
            cout << e->other(s);
            e->wt(cout) << " -> ";
        }
        cout << endl;
    }
    cout << endl;
}

template <class Graph, class Edge>
void IO<Graph, Edge>::showEdges(const Graph &G) {
    const vector<Edge *> vec = edges<Graph, Edge>(G);
    for (typename vector<Edge *>::const_iterator p = vec.begin(); p != vec.end(); ++p) {
        (*p)->show();
    }
}

template <class Graph, class Edge>
void IO<Graph, Edge>::showAdj(const Graph &G) {
    const int DEFAULT_WIDTH = 5;

    for (int i = 0; i < DEFAULT_WIDTH; i++) cout << ' ';
    cout << " |";
    for (int i = 0; i < G.V(); i++) {
        cout.width(DEFAULT_WIDTH);
        cout << i;
    }
    cout << endl;
    for (int i = 0; i <= G.V(); i++) {
        for (int j = 0; j < DEFAULT_WIDTH; j++) cout << '-';
    }
    cout << "--" << endl;

    for (int v = 0; v < G.V(); v++) {
        cout.width(DEFAULT_WIDTH);
        cout << v << " |";

        for (int w = 0; w < G.V(); w++) {
            cout << " ";
            G.edge(v, w) ? G.edge(v, w)->wt(cout) : (cout << "   *");
        }
        cout << endl;
    }
    cout << endl;
}

template <class Graph, class Edge>
void IO<Graph, Edge>::scanEZ(Graph &G) {
    int v, w;
    double wt;
    while (!isTerminateInput()) {
        cin >> v >> w >> wt;
        if (v < 0 || v >= G.V() || w < 0 || w >= G.V()) {
            cerr << "Out of range" << endl;
            continue;
        }
        G.insert(new Edge(v, w, wt));
    }
}

template <class Graph, class Edge>
void IO<Graph, Edge>::scan(Graph &G) {
    string v, w;
    double wt;
    ST st;
    while (!isTerminateInput()) {
        cin >> v >> w;
        G.insert(new Edge(st.index(v), st.index(w), wt));
    }
}

template <class Graph, class Edge>
bool IO<Graph, Edge>::isTerminateInput(int deep) {
    if (deep == 0) return true;
    char c = cin.get();
    if (c == '\n') return isTerminateInput(deep - 1);
    else cin.putback(c);
    return false;
}

#endif
