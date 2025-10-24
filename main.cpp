#include <iostream>
#include <string>
#include "SparseMatrix.h"
using namespace std;
#include <ctime>
#include <cstdlib>
#include <set>
#include <vector>
vector<pair<int, int>> generateUniquePositions(int numPositions, int maxX, int maxY) {
    set<pair<int, int>> positionsSet;
    vector<pair<int, int>> positions;
    srand(static_cast<unsigned int>(time(0)));
    while (positionsSet.size() < numPositions) {
        int x = rand() % maxX;
        int y = rand() % maxY;
        pair<int, int> pos = make_pair(x, y);
        if (positionsSet.find(pos) == positionsSet.end()) {
            positionsSet.insert(pos);
            positions.push_back(pos);
        }
    }
    return positions;
}
double measureAdditionTime(SparseMatrix& matrixA, SparseMatrix& matrixB, SparseMatrix& resultMatrix, int numOperations, int maxX, int maxY) {
    auto positions = generateUniquePositions(numOperations, maxX, maxY);
    srand(static_cast<unsigned int>(time(0)));
    clock_t startTime = clock();
    for (const auto& pos : positions) {
        int valueA = matrixA.get(pos.first, pos.second);
        int valueB = matrixB.get(pos.first, pos.second);
        int sum = valueA + valueB;
        if (sum != 0) {
            resultMatrix.add(sum, pos.first, pos.second);
        }
    }
    clock_t endTime = clock();
    return static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
}
double measureMultiplicationTime(SparseMatrix& matrixA, SparseMatrix& matrixB) {
    clock_t startTime = clock();
    SparseMatrix* result = matrixA.multiply(&matrixB);
    clock_t endTime = clock();
    delete result;
    return static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
}
double measureGetTime(SparseMatrix& matrix, int numOperations, int maxX, int maxY) {
    auto positions = generateUniquePositions(numOperations, maxX, maxY);
    srand(static_cast<unsigned int>(time(0)));
    clock_t startTime = clock();
    for (const auto& pos : positions) {
        matrix.get(pos.first, pos.second);
    }
    clock_t endTime = clock();
    return static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
}

int main() {
    SparseMatrix matrixA;
    matrixA.add(5, 0, 1);
    matrixA.add(3, 2, 3);
    cout << "Matrix A:" << endl;
    matrixA.printStoredValues();
    cout << "Valor en (0,1): " << matrixA.get(0, 1) << endl;
    cout << "Valor en (1,1): " << matrixA.get(1, 1) << endl;
    int numElements=50;
    int maxX=20;
    int maxY=20;
    auto positions = generateUniquePositions(numElements, maxX, maxY);
    SparseMatrix randomMatrix;
    for (const auto& pos : positions) {
        int value = rand() % 10 + 1;
        randomMatrix.add(value, pos.first, pos.second);
    }
    cout << "Matriz random:" << endl;
    randomMatrix.printStoredValues();
    cout << "Densidad: " << randomMatrix.density() << "%" << endl;
    srand(time(0));
    vector<int> sizes = {50, 250, 500, 1000, 5000};
    for (int size : sizes) {
        SparseMatrix matALow, matBLow, resultAddLow, resultMulLow;
        int numElementsLow = (size * size * 35) / 100;
        SparseMatrix matAHigh, matBHigh, resultAddHigh, resultMulHigh;
        int numElementsHigh = (size * size * 75) / 100;
        auto positionsALow = generateUniquePositions(numElementsLow, size, size);
        auto positionsBLow = generateUniquePositions(numElementsLow, size, size);
        auto positionsAHigh = generateUniquePositions(numElementsHigh, size, size);
        auto positionsBHigh = generateUniquePositions(numElementsHigh, size, size);
        for (const auto& pos : positionsALow) {
            matALow.add(rand() % 10 + 1, pos.first, pos.second);
        }
        for (const auto& pos : positionsBLow) {
            matBLow.add(rand() % 10 + 1, pos.first, pos.second);
        }
        for (const auto& pos : positionsAHigh) {
            matAHigh.add(rand() % 10 + 1, pos.first, pos.second);
        }
        for (const auto& pos : positionsBHigh) {
            matBHigh.add(rand() % 10 + 1, pos.first, pos.second);
        }
        double totalAddLow = 0, totalMultiplicarLow = 0, totalGetLow = 0;

        cout << "\nSize " << size << "x" << size << " (Densidad baja menor a 40%):" << endl;
          for (int i = 0; i < 10; i++) {
            double timeAddLow = measureAdditionTime(matALow, matBLow, resultAddLow, numElementsLow, size, size);
            double timeMultiplicarLow = measureMultiplicationTime(matALow, matBLow);
            double timeGetLow = measureGetTime(matALow, numElementsLow, size, size);
            cout << "Iteracion " << i+1 << " - Add: " << timeAddLow << "s, Multiplicar: " << timeMultiplicarLow << "s, Get: " << timeGetLow << "s" << endl;
            totalAddLow += timeAddLow;
            totalMultiplicarLow += timeMultiplicarLow;
            totalGetLow += timeGetLow;
        }
        cout << "Add promedio: " << totalAddLow / 10.0 << "s" << endl;
        cout << "Mul promedio: " << totalMultiplicarLow / 10.0 << "s" << endl;
        cout << "Get promedio: " << totalGetLow / 10.0 << "s" << endl;
        double timeAddHigh, timeMultiplicarHigh, timeGetHigh;
        cout << "Size " << size << "x" << size << " (Densidad Alta mayor a 70%):" << endl;
        double totalAddHigh = 0, totalMulHigh = 0, totalGetHigh = 0;
        for (int i = 0; i < 10; i++) {
            double timeAddHigh = measureAdditionTime(matAHigh, matBHigh, resultAddHigh, numElementsHigh, size, size);
            double timeMultiplicarHigh = measureMultiplicationTime(matAHigh, matBHigh);
            double timeGetHigh = measureGetTime(matAHigh, numElementsHigh, size, size);
            cout << "Iteracion " << i+1 << " - Add: " << timeAddHigh << "s, Multiplicar: " << timeMultiplicarHigh << "s, Get: " << timeGetHigh << "s" << endl;
            totalAddHigh += timeAddHigh;
            totalMulHigh += timeMultiplicarHigh;
            totalGetHigh += timeGetHigh;
        }
        cout << "Add promedio: " << totalAddHigh / 10.0 << endl;
        cout << "Mul promedio: " << totalMulHigh / 10.0 << endl;
        cout << "Get promedio: " << totalGetHigh / 10.0 << endl;
    }

    return 0;
}
