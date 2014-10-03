#include "WeightedEdge.cc"
#include "DenseGRAPH.cc"
#include "SparseMultiGRAPH.cc"
#include "IO.cc"

#include "MSTpr.cc"
#include "MSTcr.cc"
#include "MSTbr.cc"

typedef WeightedEdge Edge;
typedef DenseGRAPH<Edge> Graph;

void graphInfo(const Graph &G) {
    // IO<Graph, Edge>::show(G);
    // IO<Graph, Edge>::showEdges(G);
    IO<Graph, Edge>::showAdj(G);
}

int main() {
    int V;
    cin >> V;
    Graph G(V);

    IO<Graph, Edge>::scanEZ(G);
    MSTbr<Graph, Edge>(G).show();

    // graphInfo(G);

    return 0;
}