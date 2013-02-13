#ifndef TCSC_CC_
#define TCSC_CC_

#include "DenseGRAPH.cc"
#include "dagTC.cc"
// #include "SCc.cc"
// #include "SCt.cc"
#include "SCg.cc"

// Программа 19.13. Транзитивное замыкание на основе сильных компонент
template <class Graph>
class TCsc {
    const Graph &G;
    DenseGRAPH *K;
    dagTC<DenseGRAPH, Graph> *Ktc;
    SCg<Graph> *Gsc;

public:
    TCsc(const Graph &G) : G(G) {
        Gsc = new SCg<Graph>(G);
        K = new DenseGRAPH(Gsc->count, true);
        for (int v = 0; v < G.V(); v++) {
            typename Graph::adjIterator A(G, v);
            for (int t = A.beg(); !A.end(); t = A.nxt()) {
                K->insert(Edge(Gsc->ID(v), Gsc->ID(t)));
            }
        }
        Ktc = new dagTC<DenseGRAPH, Graph>(*K);
    }

    ~TCsc() {
        delete K;
        delete Ktc;
        delete Gsc;
    }

    bool reachable(int v, int w) const {
        return Ktc->reachable(Gsc->ID(v), Gsc->ID(w));
    }
};

#endif
