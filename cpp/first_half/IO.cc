#ifndef IO_CC_
#define IO_CC_

#include <iostream>
#include <cstdlib>
#include <map>
#include "Edge.cc"
#include "ST.cc"
// #include "MapST.cc"
// typedef MapST ST;
#include "clients.cc"

using namespace std;

// Программа 17.4 (расширенная). Интерфейс ввода/вывода для функций обработки графов
template <class Graph>
class IO {
public:
    static void show(const Graph &G);
    static void showEdges(const Graph &G);
    static void showAdj(const Graph &G);

    static void scanEZ(Graph &G);
    static void scan(Graph &G);

    static void randE(Graph &G, int E);
    static void randG(Graph &G, int E);

private:
    static bool isTerminateInput(int deep = 2);
};

// Программа 17.3. Клиентская функция печати графа
template <class Graph>
void IO<Graph>::show(const Graph &G) {
    for (int s = 0; s < G.V(); s++) {
        cout.width(2);
        cout << s << ": ";
        typename Graph::adjIterator A(G, s);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (t == -1) continue;
            cout.width(2);
            cout << t << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Упражнение 17.14
template <class Graph>
void IO<Graph>::showEdges(const Graph &G) {
    const vector<Edge> vec = edges(G);
    for (vector<Edge>::const_iterator p = vec.begin(); p != vec.end(); ++p) {
        cout << p->v << "-" << p->w << " ";
    }
    cout << '\n' << endl;
}

// Упражнение 17.18
template <class Graph>
void IO<Graph>::showAdj(const Graph &G) {
    const int DEFAULT_WIDTH = (G.V() < 11) ? 2 : 3;

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
            cout.width(DEFAULT_WIDTH);
            cout << G.edge(v, w);
        }
        cout << endl;
    }
    cout << endl;
}

// Упражнение 17.12
template <class Graph>
bool IO<Graph>::isTerminateInput(int deep) {
    if (deep == 0) return true;
    char c = cin.get();
    if (c == '\n') return isTerminateInput(deep - 1);
    else cin.putback(c);
    return false;
}
template <class Graph>
void IO<Graph>::scanEZ(Graph &G) {
    int v, w;
    while (true) {
        if (isTerminateInput()) break;

        cin >> v >> w;
        if (v < 0 || v >= G.V() || w < 0 || w >= G.V()) {
            cerr << "Out of range" << endl;
            continue;
        }
        G.insert(Edge(v, w));
    }
}

// Программа 17.14. Построение графа из пар символов
template <class Graph>
void IO<Graph>::scan(Graph &G) {
    string v, w;
    ST st;
    while (true) {
        if (isTerminateInput()) break;

        cin >> v >> w;
        G.insert(Edge(st.index(v), st.index(w)));
    }
}

// Программа 17.12. Генератор случайных графов (случайные рёбра)
template <class Graph>
void IO<Graph>::randE(Graph &G, int E) {
    int v, w;
    for (int i = 0; i < E; ++i) {
        v = rand() % G.V();
        w = rand() % G.V();
        G.insert(Edge(v, w));
    }
}

// Программа 17.13. Генератор случайных графов (случайный граф)
template <class Graph>
void IO<Graph>::randG(Graph &G, int E) {
    double p = 2.0 * E / G.V() / (G.V() - 1);
    for (int i = 0; i < G.V(); i++) {
        for (int j = 0; j < i; j++) {
            if (rand() < p * RAND_MAX) G.insert(Edge(i, j));
        }
    }
}

#endif
