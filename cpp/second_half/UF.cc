#ifndef UF_CC_
#define UF_CC_

// Программа 4.11. Реализация АДТ "Отношения эквивалентности"
class UF {
    int *id, *sz;

public:
    UF(int N) {
        id = new int[N];
        sz = new int[N];
        for (int i = 0; i < N; i++) {
            id[i] = i;
            sz[i] = 1;
        }
    }

    ~UF() {
        delete [] sz;
        delete [] id;
    }

    int find(int x) const {
        while (x != id[x]) x = id[x];
        return x;
    }

    int find(int p, int q) const {
        return (find(p) == find(q));
    }

    void unite(int p, int q) {
        int i = find(p), j = find(q);
        if (i == j) return;
        if (sz[i] < sz[j]) {
            id[i] = j;
            sz[j] += sz[i];
        } else {
            id[j] = i;
            sz[i] += sz[j];
        }
    }
};

#endif