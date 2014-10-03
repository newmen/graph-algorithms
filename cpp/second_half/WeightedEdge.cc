#ifndef WEIGHTEDEDGE_CC_
#define WEIGHTEDEDGE_CC_

#include <iostream>
using namespace std;

// Упражнение 20.8
class WeightedEdge {
    int _v, _w;
    double _wt;

public:
    WeightedEdge(int v, int w, double wt) : _v(v), _w(w), _wt(wt) {}

    int v() const { return _v; }
    int w() const { return _w; }
    double wt() const { return _wt; }

    bool from(int v) const { return _v == v; }
    int other(int v) const { return from(v) ? _w : _v; }

    void show() const {
        cout << _v << "-" << _w;
        wt(cout) << endl;
    }

    ostream &wt(ostream &os) const {
        os << " ." << (int)(_wt * 100 + 0.5);
        return os;
    }
};

#endif
