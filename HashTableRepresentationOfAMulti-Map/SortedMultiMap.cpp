#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

/// Θ(m) - wir kopieren alles in ein neues SMM.
void SortedMultiMap::resize_rehash() {
    int oldcap = this->m;
    this->m *= 2;
    /// Wir initialisieren das neue SMM.
    SMM *new_T = new SMM[this->m];
    for (int i = 0; i < m; i++) {
        new_T[i].key = -1;
        new_T[i].length = 0;
        new_T[i].capacity = 10;
        new_T[i].values = new TValue [new_T[i].capacity];
    }

    /// Wir kopieren alles, was im alten SMM war, in das neue SMM.
    for (int i = 0; i < oldcap; i++){
        if (this->T[i].key != -1 && this->T[i].key != DELETE) {
            int d = 0;
            int pos = this->h(this->T[i].key, d);

            while (pos < m && new_T[pos].key != -1) {
                d++;
                pos = this->h(this->T[i].key, d);
            }

            new_T[pos].key = this->T[i].key;
            new_T[pos].length = this->T[i].length;
            new_T[pos].capacity = this->T[i].capacity;
            for (int j = 0; j < new_T[pos].length; j++) {
                new_T[pos].values[j] = this->T[i].values[j];
            }
            delete[] this->T[i].values;
        }
    }
    delete[] this->T;
    this->T = new_T;

}

/// Θ(m) - Wir initialisieren alles.
SortedMultiMap::SortedMultiMap(Relation r) {
    this->lengthSMM = 0;
    this->m = 11;
    this->r = r;
    this->T = new SMM[this->m];

    for(int i = 0; i < m; i++) {
        this->T[i].key = -1;
        this->T[i].length = 0;
        this->T[i].capacity = 10;
        this->T[i].values = new TValue[this->T[i].capacity];
    }
}

/// Best: Θ(1) - Wenn die Position für das neue Schlüssel-Wert-Paar sofort und ohne Kollisionen gefunden wird.
/// Average: Θ(1) - der Annahme eines guten Hash-Funktionsverhaltens.
/// Worst: Θ(m) - wennn resize_rehash wird benutzt.
/// Allgemeine: O(m)
void SortedMultiMap::add(TKey c, TValue v) {
    int i = 0;
    int pos = this->h(c, i);

    while(this->T[pos].key != -1 && i < this->m && this->T[pos].key != c ) {
        i++;
        pos = this->h(c, i);
    }
    /// Wenn die Schlussel schon existiert und wir mussen die Wert fugen
    if (i < this->m && this->T[pos].key == c) {
        if (this->T[pos].length < this->T[pos].capacity)
            this->T[pos].values[this->T[pos].length++] = v;
        else {
            int newCap = this->T[pos].capacity * 2;
            TValue *newArr = new TValue[newCap];
            for(int j = 0; j < this->T[pos].length; j++)
                newArr[j] = this->T[pos].values[j];
            this->T[pos].capacity = newCap;
            delete[] this->T[pos].values;
            this->T[pos].values = newArr;
            this->T[pos].values[this->T[pos].length++] = v;
        }

    }
    /// Hir fugen wir eine neue Schlussel ein mit den Wert v.
    else {

        i = 0;
        pos = this->h(c, i);

        while (this->T[pos].key != -1 && i < this->m && this->T[pos].key != DELETE) {
            i++;
            pos = this->h(c, i);
        }
        if (i < this->m && this->T[pos].key == -1 || this->T[pos].key == DELETE) {
            this->T[pos].key = c;
            this->T[pos].values[this->T[pos].length++] = v;
        }
        else {
            resize_rehash();
            return this->add(c, v);
        }
    }
    this->lengthSMM++;
}

/// Best: Θ(1) - Wenn die Position für das Schlüssel sofort und ohne Kollisionen gefunden wird.
/// Average: Θ(1)
/// Worst: Θ(m) - wenn wir mussen durch den gantzen SMM durchfahren.
/// Allgemeine: O(m)
vector<TValue> SortedMultiMap::search(TKey c) const {
    int i = 0;
    vector<TValue> val;
    int pos = this->h(c, i);
    while(i < this->m && this->T[pos].key != -1) {
        if (this->T[pos].key == c)
            for (int j = 0; j < this->T[pos].length; j++)
                val.push_back(this->T[pos].values[j]);
        i++;
        pos = this->h(c, i);
    }
	return val;
}

/// Best: Θ(1) - wenn die Schlussel nicht existiert.
/// Average: Θ(m) -
/// Worst: Θ(m) - wenn wir mussen durch den gantzen SMM durchfahren.
/// Allgemeine: O(m)
bool SortedMultiMap::remove(TKey c, TValue v) {
    int i = 0;
    int pos = this->h(c, i);

    /// Wenn wir die Schlussel finden , uberschreiben wir die Wert v.
    while (i < this->m && this->T[pos].key != -1) {
        if (this->T[pos].key == c) {
            for (int j = 0; j < this->T[pos].length; j++) {
                if (this->T[pos].values[j] == v) {
                    for (int k = j; k < this->T[pos].length - 1; k++) {
                        this->T[pos].values[k] = this->T[pos].values[k + 1];
                    }
                    this->T[pos].length--;
                    if (this->T[pos].length == 0) {
                        this->T[pos].key = DELETE;
                    }
                    this->lengthSMM--;
                    return true;
                }
            }
        }
        i++;
        pos = this->h(c, i);
    }
    return false;
}

/// Θ(1)
int SortedMultiMap::size() const {
    return this->lengthSMM;
}

/// Θ(1)
bool SortedMultiMap::isEmpty() const {
	return this->lengthSMM == 0;
}

/// Θ(1)
SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

/// Θ(m)
SortedMultiMap::~SortedMultiMap() {
    for (int i = 0; i < this->m; i++)
        delete[] this->T[i].values;
    delete[] this->T;
}
