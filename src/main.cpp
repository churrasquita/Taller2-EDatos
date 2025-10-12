#include "SparseMatrix.h"
#include <iostream>
using namespace std;

int main() {
    SparseMatrix s;
    s.add(0, 2, 5);
    s.add(2, 1, 8);
    s.add(3, 3, 9);
    s.add(2, 1, 7); // reemplaza valor anterior
    s.printStoredValues();
    return 0;
}