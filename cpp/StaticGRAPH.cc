#ifndef STATICGRAPH_CC_
#define STATICGRAPH_CC_

#include <vector>
#include "Edge.cc"

using namespace std;

// Упражнение 17.51

class StaticGRAPH {
public:
    StaticGRAPH(const vector<Edge> &);
    ~StaticGRAPH();
    
    int V() const;
    int E() const;
    bool directed() const;
    
    void insert(const Edge &);
    void remove(const Edge &);
    bool edge(int, int) const;

    void insert();
    void remove(int);

    void removeLoopsAndParallels();

    class adjIterator {
    public:
        adjIterator(const StaticGRAPH &, int);
        int beg();
        int nxt();
        bool end();
    };
};

#endif
