#ifndef STATICMULTIGRAPH_CC_
#define STATICMULTIGRAPH_CC_

#include <algorithm>
#include <vector>
#include "Edge.cc"
#include "EdgeSorter.h"

using namespace std;

// Упражнение 17.52

class StaticMultiGRAPH {
    struct node {
        // int cnt; // wtf??
        vector<int> edges;
    };

public:
    class adjIterator;
    friend class adjIterator;

    StaticMultiGRAPH(int V, bool digraph = false) : Ecnt(0), digraph(digraph), adj(V) {}

    StaticMultiGRAPH(const vector<Edge> &edges, bool digraph = false) :
        Ecnt(0), digraph(digraph)
    {
        const vector<Edge> &sortedEdges = sortEdges(edges);
        for (vector<Edge>::const_iterator p = sortedEdges.begin(); p != sortedEdges.end(); ++p) {
            insert(*p);
        }
    }
    
    int V() const { return (int)adj.size(); }
    int E() const { return Ecnt; }
    bool directed() const { return digraph; }
    
    void insert(const Edge &e) {
        simpleInsert(e.v, e.w);
        if (!digraph && e.v != e.w) simpleInsert(e.w, e.v);
        ++Ecnt;
    }

    void remove(const Edge &e) {
        if (!edge(e.v, e.w)) return;
        simpleRemove(e.v, e.w);
        if (!digraph && e.v != e.w) simpleRemove(e.w, e.v);
        --Ecnt;
    }

    bool edge(int v, int w) const {
        return find(adj[v].edges.begin(), adj[v].edges.end(), w) != adj[v].edges.end();
    }

    void insert() {
        adj.push_back(node());
    }

    void remove(int v) {
        Ecnt -= adj[v].edges.size();
        adj.erase(adj.begin() + v);
        for (vector<node>::iterator p = adj.begin(); p != adj.end(); ++p) {
            for (vector<int>::iterator i = p->edges.begin(); i != p->edges.end(); ) {
                if (*i == v) {
                    p->edges.erase(i);
                } else {
                    if (*i > v) --(*i);
                    ++i;
                }
            }
        }
    }

    // Упражнение 17.53
    void removeLoopsAndParallels() {
        vector<int> around;
        for (int v = 0; v < V(); ++v) {
            around.clear();
            for (vector<int>::iterator i = adj[v].edges.begin(); i != adj[v].edges.end(); ) {
                if (*i == v) {
                    adj[v].edges.erase(i);
                    --Ecnt;
                } else if (find(around.begin(), around.end(), *i) != around.end()) {
                    adj[v].edges.erase(i);
                    if (!digraph) simpleRemove(*i, v);
                    --Ecnt;
                } else {
                    around.push_back(*i);
                    ++i;
                }
            }
        }
    }

private:
    void simpleInsert(int v, int w) {
        if (v >= (int)adj.size()) adj.push_back(node());
        adj[v].edges.push_back(w);
    }

    void simpleRemove(int v, int w) {
        vector<int>::iterator p = find(adj[v].edges.begin(), adj[v].edges.end(), w);
        if (p != adj[v].edges.end()) adj[v].edges.erase(p);
    }

private:
    int Ecnt;
    bool digraph;
    vector<node> adj;
};

class StaticMultiGRAPH::adjIterator {
public:
    adjIterator(const StaticMultiGRAPH &G, int v) :
        G(G), v(v), i(G.adj[v].edges.begin()) {}

    int beg() {
        i = G.adj[v].edges.begin();
        return (end()) ? -1 : *i;
    }

    int nxt() {
        return *(++i);
    }

    bool end() {
        return i == G.adj[v].edges.end();
    }

private:
    const StaticMultiGRAPH &G;
    int v;
    vector<int>::const_iterator i;
};

#endif
