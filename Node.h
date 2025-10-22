#ifndef NODO_H
#define NODO_H
class Node {
    public:
    int valor;
    int xPosicion;  
    int yPosicion;
    Node* next; 
    Node(int val, int x, int y) : valor(val), xPosicion(x), yPosicion(y), next(nullptr) {}

};
#endif 