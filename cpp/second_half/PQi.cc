#ifndef PQI_CC_
#define PQI_CC_

#include <vector>
using namespace std;

// Программа 20.10. Реализация очереди с приоритетами в виде многопозиционного частично упорядоченного полного дерева
template <class keyType>
class PQi {
    const vector<keyType> &a;
    vector<int> pq, qp;
    int d, N;

    void exch(int i, int j) {
        int t = pq[i];
        pq[i] = pq[j];
        pq[j] = t;
        qp[pq[i]] = i;
        qp[pq[j]] = j;
    }

    void fixUp(int k) {
        int kd;
        while (k > 1 && a[(kd = pq[(k+d-2)/d)]] > a[pq[k]]) {
            exch(k, kd);
            k = kd;
        }
    }

    void fixDown(int k, int N) {
        int j;
        while ((j = d*(k-1)+2) <= N) {
            for (int i = j+1; i < j+d && i <= N; i++) {
                if (a[pq[j]] > a[pq[i]]) j = i;
            }
            if (!(a[pq[k]] > a[pq[j]])) break;
            exch(k, j);
            k = j;
        }
    }

public:
    PQi(int N, const vector<keyType> &a, int d = 3) :
        a(a), pq(N+1, 0), qp(N+1, 0), N(0), d(d) {}

    int empty() const { return N == 0; }

    void insert(int v) {
        pq[++N] = v;
        qp[v] = N;
        fixUp(N);
    }

    int getmin() {
        exch(1, N);
        fixDown(1, N-1);
        return pq[N--];
    }

    void lower(int k) {
        fixUp(qp[k]);
    }
};

#endif
