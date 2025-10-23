#include <iostream>
#include <string>
#include "SparseMatrix.h"
using namespace std;
int main() {
    SparseMatrix matrixA;
    matrixA.add(5, 0, 1);
    matrixA.add(3, 2, 3);
    cout << "Matrix A:" << endl;
    matrixA.printStoredValues();
    cout << "Valor en (0,1): " << matrixA.get(0, 1) << endl;
    cout << "Valor en (1,1): " << matrixA.get(1, 1) << endl;
    return 0;
}