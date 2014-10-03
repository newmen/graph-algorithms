#ifndef SORT_CC_
#define SORT_CC_

// Программа 6.1. Пример сортировки массива с помощью управляющей программы

#include <iostream>
#include <cstdlib>
using namespace std;

template <class Item>
void exch(Item &A, Item &B) {
    Item t = A;
    A = B;
    B = t;
}

template <class Item>
void complexch(Item &A, Item &B) {
    if (B < A) exch(A, B);
}

template <class Item>
void sort(Item a[], int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        for (int j = i; j < l; j--) {
            complexch(a[j - 1], a[j]);
        }
    }
}

#endif

// int main(int argc, char *argv[]) {
//     int i, N = atoi(argv[1]), sw = atoi(argv[2]);
//     int *a = new int[N];
//     if (sw) {
//         for (i = 0; i < N; i++) {
//             a[i] = 1000 * (1.0 * rand() / RAND_MAX);
//         }
//     } else {
//         N = 0;
//         while (cin >> a[N]) N++;
//     }

//     sort(a, 0, N - 1);

//     for (i = 0; i < N; i++) cout << a[i] << " ";
//     cout << endl;
// }
