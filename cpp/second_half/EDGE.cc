#ifndef EDGE_CC_
#define EDGE_CC_

// Программа 20.1. Интерфейс АДТ взвешенного ребра

class EDGE {
public:
    EDGE(int, int, double);
    int v() const;
    int w() const;
    double wt() const;
    bool from(int) const;
    int other(int) const;
};

#endif