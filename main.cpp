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
    return 0;
}