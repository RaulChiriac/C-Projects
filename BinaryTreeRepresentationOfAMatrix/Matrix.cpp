#include "Matrix.h"
#include <exception>
#include <stack>
using namespace std;

/// Θ(1)
Matrix::Matrix(int nrLines, int nrCols) {
    if (nrLines <= 0 || nrCols <= 0)
        throw exception();
    this->linesNr = nrLines;
    this->colsNr = nrCols;
    this->root = -1;
    this->capacity = 10;
    this->firstEmpty = 0;
    this->array = new BSTNode[this->capacity];
    for (int i = 0; i < capacity - 1; i++)
        this->array[i].left = i + 1;
    this->array[capacity - 1].left = -1;
}

/// Θ(1)
int Matrix::nrLines() const {
    return this->linesNr;
}

/// Θ(1)
int Matrix::nrColumns() const {
    return this->colsNr;
}

/// Θ(1)
bool Matrix::relation(int i1, int j1, int i2, int j2) const {
    if (i1 < i2)
        return true;
    else if (i1 > i2)
        return false;
    return j1 <= j2;
}

/// Best: Θ(1) - Wurzel
/// Average: Θ(log n) - balansiert (AVL)
/// Worst: Θ(n) - unbalansiert
/// Allgemeine: O(n)
TElem Matrix::element(int i, int j) const {
    if (i < 0 || i >= linesNr || j < 0 || j >= colsNr)
        throw exception(); // Invalid position
    int current = this->root;
    while (current != -1) {
        if (this->array[current].info.i == i && this->array[current].info.j == j)
            return this->array[current].info.elem;
        if (relation(i, j, this->array[current].info.i, this->array[current].info.j))
            current = this->array[current].left;
        else
            current = this->array[current].right;
    }
    return NULL_TELEM;
}

/// Θ(1) Amortisierte
int Matrix::allocate() {
    if (firstEmpty == -1) {
        // kein meher Platz , mussen wir die capacity doppelt.
        int newCapacity = capacity * 2;
        BSTNode* newArray = new BSTNode[newCapacity];
        for (int i = 0; i < capacity; i++) {
            newArray[i] = array[i];
        }
        for (int i = capacity; i < newCapacity - 1; i++) {
            newArray[i].left = i + 1;
        }
        newArray[newCapacity - 1].left = -1;
        firstEmpty = capacity;
        capacity = newCapacity;
        delete[] array;
        array = newArray;
    }
    int newPos = firstEmpty;
    firstEmpty = array[firstEmpty].left;
    array[newPos].left = -1;
    array[newPos].right = -1;
    return newPos;
}

/// Θ(1)
void Matrix::deallocate(int position) {
    array[position].left = firstEmpty;
    firstEmpty = position;
}

/// Best: Θ(1) - kein linke Unterbaum.
/// Average: Θ(log n) - balansiert
/// Wors: Θ(n) - unbalansiert
/// Allgemeine: O(n)
int Matrix::minimum(int node) const {
    while (array[node].left != -1) {
        node = array[node].left;
    }
    return node;
}

/// Θ(1)
void Matrix::removeNode(int node) {
    int parent = array[node].parent;
    if (array[node].left == -1 && array[node].right == -1) { // Ohne Kinder
        if (node == root) {
            root = -1;
        } else {
            if (array[parent].left == node) {
                array[parent].left = -1;
            } else {
                array[parent].right = -1;
            }
        }
        deallocate(node);
    } else if (array[node].left == -1 || array[node].right == -1) { // Ein Kind
        int child = (array[node].left != -1) ? array[node].left : array[node].right;
        if (node == root) {
            root = child;
        } else {
            if (array[parent].left == node) {
                array[parent].left = child;
            } else {
                array[parent].right = child;
            }
        }
        array[child].parent = parent;
        deallocate(node);
    } else { // Zwei Kinder
        int successor = minimum(array[node].right);
        array[node].info = array[successor].info;
        removeNode(successor);
    }
}

/// Best: Θ(1) - Wurzel
/// Average: Θ(log n) - balansiert
/// Worst: Θ(n) - unbalansiert
/// Allgemeine: O(n)
TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || i >= linesNr || j < 0 || j >= colsNr)
        throw exception(); // Ungultige Position

    int current = this->root;
    int parent = -1;
    bool isLeftChild = true;

    while (current != -1 && !(this->array[current].info.i == i && this->array[current].info.j == j)) {
        parent = current;
        if (relation(i, j, this->array[current].info.i, this->array[current].info.j)) {
            current = this->array[current].left;
            isLeftChild = true;
        } else {
            current = this->array[current].right;
            isLeftChild = false;
        }
    }

    if (current != -1) { // Element gefunden
        TElem oldValue = this->array[current].info.elem;
        if (e == NULL_TELEM) { // Entfernen des Elements
            removeNode(current);
        } else { // Aktualisieren des Elements
            this->array[current].info.elem = e;
        }
        return oldValue;
    } else { // Element nicht gefunden, neues Element einfügen
        if (e == NULL_TELEM) {
            return NULL_TELEM; // Keine Änderung erforderlich
        }
        int newNode = allocate();
        this->array[newNode].info = {i, j, e};
        this->array[newNode].parent = parent;
        if (parent == -1) {
            this->root = newNode; // Der Baum war leer
        } else if (isLeftChild) {
            this->array[parent].left = newNode;
        } else {
            this->array[parent].right = newNode;
        }
        return NULL_TELEM;
    }
}

/// Θ(1)
Matrix::~Matrix() {
    delete[] this->array;
}

/// Θ(n) - n ist die Anzahl der Knoten im Baum
void Matrix::resize(int newLines, int newCols) {
    if (newLines <= 0 || newCols <= 0) {
        throw exception(); // Ungultige Grosse.
    }

    stack<int> nodes; // fur Knoten
    if (root != -1) {
        nodes.push(root);
    }

    while (!nodes.empty()) {
        int current = nodes.top();
        nodes.pop();

        if (array[current].info.i >= newLines || array[current].info.j >= newCols) {
            removeNode(current); // ob current i oder j grosser als neues i oder j ist dann man remove current.
        } else { // ob nicht wir gehen weiter zu den Kinder.
            if (array[current].right != -1) {
                nodes.push(array[current].right);
            }
            if (array[current].left != -1) {
                nodes.push(array[current].left);
            }
        }
    }

    this->linesNr = newLines; // Wir ändern die Dimensionen
    this->colsNr = newCols;
}
