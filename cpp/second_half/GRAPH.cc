#ifndef GRAPH_CC_
#define GRAPH_CC_

// Программа 20.1. Интерфейс АДТ графа со взвешенными рёбрами

template <class Edge>
class GRAPH {
public:
    GRAPH(int, bool);
    ~GRAPH();

    int V() const;
    int E() const;
    bool directed() const;

    int insert(Edge *);
    int remove(Edge *);
    Edge *edge(int, int);

    class adjIterator {
        adjIterator(const GRAPH &, int);
        Edge *beg();
        Edge *nxt();
        bool end();
    };
};

#endif