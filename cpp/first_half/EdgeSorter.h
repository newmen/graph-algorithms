#ifndef EDGESORTER_H_
#define EDGESORTER_H_

#include <vector>
#include "Edge.cc"

using namespace std;

struct EdgeSorter {
    bool operator () (const Edge &a, const Edge &b) {
        if (a.v == b.v && a.w == b.w) return true;
        return (a.v <= b.v && a.w < b.w);
    }
};

vector<Edge> sortEdges(const vector<Edge> &edges);

#endif