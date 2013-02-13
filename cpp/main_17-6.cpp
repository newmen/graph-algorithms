#include <iostream>
#include <cstdlib>
#include "GRAPH.cc"
#include "IO.cc"
#include "CC.cc"

using namespace std;

// Программа 17.6. Пример клиентской программы обработки графов
int main(int argc, char *argv[]) {
    int V = atoi(argv[1]);
    GRAPH G(V);
    IO<GRAPH>::scan(G);
    if (V < 20) IO<GRAPH>::show(G);
    cout << G.E() << " edges ";
    CC<GRAPH> Gcc(G);
    cout << Gcc.count() << " components" << endl;
    return 0;
}