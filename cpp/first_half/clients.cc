#ifndef BASIC_CC_
#define BASIC_CC_

#include <iostream>
#include <vector>
#include "Edge.cc"
#include "DEGREE.cc"

using namespace std;

// Программа 17.2. Пример клиентской функции обработки графов
template <class Graph>
vector<Edge> edges(const Graph &G) {
    int E = 0;
    vector<Edge> a(G.E());
    for (int v = 0; v < G.V(); v++) {
        typename Graph::adjIterator A(G, v);
        for (int w = A.beg(); !A.end(); w = A.nxt()) {
            if (G.directed() || v <= w) a[E++] = Edge(v, w);
        }
    }
    return a;
}

// Упражнение 17.13
template <class Graph>
void addEdgesFromVectorToGraph(Graph &G, const vector<Edge> &vec) {
    for (vector<Edge>::const_iterator p = vec.begin(); p != vec.end(); ++p) {
        G.insert(*p);
    }
}

// Упражнение 17.26
template <class Graph>
bool hasSeqClique(const Graph &G, int beg, int end) {
    if (beg == end) return true;
    return G.edge(beg, end) && hasSeqClique(G, beg + 1, end);
}
template <class Graph>
void findMaxSeqClique(const Graph &G) {
    int beg = -1, end = -1;
    int v = 0, w;
    while (v < G.V() - 1) {
        w = 0;
        while (v + w + 1 < G.V() && hasSeqClique(G, v, v + w + 1)) ++w;
        if (w > 2 && w > end - beg) {
            beg = v;
            end = v + w;
            v += w;
        } else {
            ++v;
        }
    }

    if (beg == -1 && end == -1) {
        cout << "No sequence cluque found" << endl;
    } else {
        cout << "Max sequence clique is: " << beg << "-" << end << endl;
    }
}

// Упражнение 17.36 (обновлённое)
template <class Graph>
Graph removeZerosLoopsParallels(const Graph &G) {
    int unzeros = 0;
    DEGREE<Graph> dg(G);
    for (int v = 0; v < G.V(); v++) {
        if (dg[v] > 0) ++unzeros;
    }

    Graph newG(unzeros);
    addEdgesFromVectorToGraph(newG, edges(G));
    newG.removeLoopsAndParallels();
    return newG;
}

// Упражнение 17.44
template <class Graph>
int zeros(const Graph &G) {
    vector<bool> rel(G.V(), false);
    vector<Edge> vec = edges(G);
    for (vector<Edge>::iterator p = vec.begin(); p != vec.end(); ++p) {
        rel[p->v] = true;
        rel[p->w] = true;
    }

    int n = 0;
    for (int v = 0; v < G.V(); ++v) {
        if (!rel[v]) ++n;
    }
    return n;
}

// Программа 19.1. Обращение орграфа
template <class inGraph, class outGraph>
void reverse(const inGraph &G, outGraph &R) {
    for (int v = 0; v < G.V(); v++) {
        typename inGraph::adjIterator A(G, v);
        for (int w = A.beg(); !A.end(); w = A.nxt()) {
            R.insert(Edge(w, v));
        }
    }
}

#endif
