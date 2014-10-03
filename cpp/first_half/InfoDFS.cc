#ifndef INFODFS_CC_
#define INFODFS_CC_

#include <iostream>
#include "SEARCH.cc"

// Упражнение 18.13, 18.14, 18.17

template <class Graph>
class InfoDFS : public SEARCH<Graph> {
    vector<int> st;
    int cntP, depth, wide;

    void eachVertex(int v) {
        printSeek();
        cout << endl;
    }

    void eachEdge(const Edge &e) {
        printEdge(e);

        cout << left;
        cout.width(22);
        printEdgeType(e);

        cout << right;
        cout.width(20 - depth * 2);
        printVec(this->ord);
        cout << "    ";
        printVec(st);

        cout << endl;
    }

    void printSeek() const {
        for (int i = 0; i < depth; ++i) cout << "  ";
    }

    void printEdge(const Edge &e) const {
        printSeek();
        cout << left;
        cout << e.v << '-';
        cout.width(3);
        cout << e.w;
    }

    void printEdgeType(const Edge &e) const {
        if (this->ord[e.w] == -1) cout << "tree link";
        else if (this->G.directed()) {
            if (st[e.w] == -1) cout << "back link";
            else if (this->ord[e.w] > this->ord[e.v]) cout << "down link";
            else cout << "cross link";
        } else {
            if (st[e.v] == e.w) cout << "parent link";
            else if (this->ord[e.w] < this->ord[e.v]) cout << "back link";
            else cout << "down link";
        }
    }

    void printVec(const vector<int> &vec) const {
        for (vector<int>::const_iterator p = vec.begin(); p != vec.end(); ++p) {
            if (p != vec.begin()) cout.width(wide);
            if (*p == -1) cout << "*";
            else cout << *p;
        }
    }

    void printHead() const {
        cout.width(48 + wide);
        if (this->G.directed()) {
            cout << "pre:";
        } else {
            cout << "ord:";
        }
        cout.width(this->G.V() * wide + 4);
        if (this->G.directed()) {
            cout << "post:";
        } else {
            cout << "ST:";
        }
        cout << endl;

        cout.width(45 + wide);
        for (int i = 0; i < this->G.V(); ++i) {
            if (i > 0) cout.width(wide);
            cout << i;
        }
        cout.width(5);
        for (int i = 0; i < this->G.V(); ++i) {
            if (i > 0) cout.width(wide);
            cout << i;
        }
        cout << '\n' << endl;
    }

protected:
    void searchC(Edge e) {
        int w = e.w;
        this->ord[e.w] = this->cnt++;
        st[e.w] = e.v;

        // eachVertex(w);
        
        typename Graph::adjIterator A(this->G, w);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            Edge o(w, t);
            eachEdge(o);

            if (this->ord[t] == -1) {
                ++depth;
                searchC(o);
            }
        }
        --depth;
    }

    // Программа 19.2. DFS на орграфе
    void searchR(Edge e) {
        int w = e.w;
        eachEdge(e);
        this->ord[w] = this->cnt++;
        ++depth;

        typename Graph::adjIterator A(this->G, w);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            Edge x(w, t);
            
            if (this->ord[t] == -1) searchR(x);
            else eachEdge(x);
        }

        st[w] = cntP++;
        --depth;
    }

    void search() {
        printHead();
        for (int v = 0; v < this->G.V(); v++) {
            if (this->ord[v] == -1) {
                depth = 0;
                Edge e = Edge(v, v);
                if (this->G.directed()) {
                    searchR(e);
                } else {
                    eachEdge(e);
                    searchC(e);
                }
            }
        }
        cout << endl;
    }

public:
    InfoDFS(const Graph &G) : SEARCH<Graph>(G), st(G.V(), -1), cntP(0), depth(0) {
        wide = G.V() < 10 ? 1 : 2;
        this->search();
    }

    int ST(int v) const { return st[v]; }
};

#endif
