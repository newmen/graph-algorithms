#include <algorithm>
#include "EdgeSorter.h"

vector<Edge> sortEdges(const vector<Edge> &edges) {
    vector<Edge> sortedEdges = edges;
    sort(sortedEdges.begin(), sortedEdges.end(), EdgeSorter());
    return sortedEdges;
}
