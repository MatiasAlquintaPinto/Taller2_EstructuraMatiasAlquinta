#include "SparseMatrix.h"
#include <iostream>
using namespace std;
SparseMatrix::SparseMatrix() : start(nullptr) {}
void SparseMatrix::add(int valor, int xPos, int yPos) {
    cout << "Agregando nodo: " << valor << " en (" << xPos << ", " << yPos << ")\n";
    if (valor == 0) return;
    Node* nuevoNodo = new Node(valor, xPos, yPos);
    if (!start) {
        start = nuevoNodo;
        return;
    }
    Node* current = start;
    Node* prev = nullptr;
    while (current && (current->xPosicion < xPos || (current->xPosicion == xPos && current->yPosicion < yPos))) {
        prev = current;
        current = current->next;
    }
    if (current && current->xPosicion == xPos && current->yPosicion == yPos) {
        current->valor = valor;
        delete nuevoNodo;
    } else {
        if (prev) {
            prev->next = nuevoNodo;
        } else {
            start = nuevoNodo;
        }
        nuevoNodo->next = current;
    }
}
int SparseMatrix::get(int xPos, int yPos) {
    Node* current = start;
    while (current) {
        if (current->xPosicion == xPos && current->yPosicion == yPos) {
            return current->valor;
        }
        current = current->next;
    }
    return 0;
}

void SparseMatrix::remove(int xPos, int yPos) {
    Node* current = start;
    Node* prev = nullptr;
    while (current) {
        if (current->xPosicion == xPos && current->yPosicion == yPos) {
            if (prev) {
                prev->next = current->next;
            } else {
                start = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void SparseMatrix::printStoredValues() {
    Node* current = start;
    while (current) {
        cout << "Valor: " << current->valor << " en posicion (x,y): (" << current->xPosicion << ", " << current->yPosicion << ")\n";
        current = current->next;
    }
}

int SparseMatrix::density() {
    int cont = 0;
    Node* current = start;
    while (current) {
        cont++;
        current = current->next;
    }
    return cont;
}
SparseMatrix::~SparseMatrix() {
    Node* current = start;
    while (current) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}
SparseMatrix* SparseMatrix::multiply(SparseMatrix* segundo) {
    SparseMatrix* resultado = new SparseMatrix();
    for (Node* nodoA = this->start; nodoA != nullptr; nodoA = nodoA->next) {
        for (Node* nodoB = segundo->start; nodoB != nullptr; nodoB = nodoB->next) {
            if (nodoA->yPosicion == nodoB->xPosicion) {
                int nuevaX = nodoA->xPosicion;
                int nuevaY = nodoB->yPosicion;
                int nuevoValor = nodoA->valor * nodoB->valor + resultado->get(nuevaX, nuevaY);
                resultado->add(nuevoValor, nuevaX, nuevaY);
            }
        }
    }
    return resultado;
}

