#ifndef MAPST_CC_
#define MAPST_CC_

#include <map>
#include <string>

using namespace std;

// Упражнение 17.63
class MapST {
public:
    MapST() : N(0) {}

    int index(const string &s) {
        if (rel.find(s) == rel.end()) rel[s] = N++;
        return rel[s];
    }

private:
    map<string, int> rel;
    int N;
};


#endif