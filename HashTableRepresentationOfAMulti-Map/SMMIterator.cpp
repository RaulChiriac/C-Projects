#include "SMMIterator.h"
#include "SortedMultiMap.h"

/// Θ(m) - Wir haben keine Stoppbedingungen
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
    int count = 0;
    for (int i = 0; i < this->map.m; i++) {
        if (this->map.T[i].key != -1 && this->map.T[i].key != DELETE) {
            count++;
        }
    }

    /// Erstellen ein Array mit der Größe der Anzahl der Schlüssel.
    this->arr = new DD[count];

    ///  Wir platzieren an jeder Position im Array einen Schlüssel und seine Elemente.
    int j = 0;
    for (int i = 0; i < this->map.m; i++) {
        if (this->map.T[i].key != -1 && this->map.T[i].key != DELETE) {
            arr[j].key = this->map.T[i].key;
            arr[j].values = this->map.T[i].values;
            arr[j].valueCount = this->map.T[i].length;
            j++;
        }
    }

    /// Fuhren ein BubbleSort nach Schlusseln nach.
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (!this->map.r(arr[j].key, arr[j + 1].key)) {
                DD temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    this->size_arr = count;
    this->key_index = 0;
    this->index = 0;
}

/// Θ(1)
void SMMIterator::first() {
    this->key_index = 0;
    this->index = 0;
}

/// Θ(1)
void SMMIterator::next() {
    if (this->valid()){
        this->index++;
        if (this->index == this->arr[this->key_index].valueCount){
            this->key_index++;
            this->index = 0;
        }
        return;
    }
    throw exception();
}

/// Θ(1)
bool SMMIterator::valid() const {
    return this->key_index < this->size_arr;
}

/// Θ(1)
TElem SMMIterator::getCurrent() const {
    if (this->valid()){
        return make_pair(this->arr[this->key_index].key, this->arr[this->key_index].values[this->index]);
    }
    throw exception();
}

void SMMIterator::modifyCurrent(TElem newElement) {
    if (this->valid()) {

        TKey currentKey = this->arr[this->key_index].key;
        TValue currentValue = this->arr[this->key_index].values[this->index];

        if (newElement.first != currentKey) {
            /// cand stergem si cheia si vvaloarea
            int i = 0;
            int pos = this->map.h(currentKey, i);
            while (this->map.T[pos].key != currentKey || this->map.T[pos].values[this->index] != currentValue) {
                i++;
                pos = this->map.h(currentKey, i);
            }
            this->map.T[pos].key = DELETE;

            /// adaugam noua pereche in SMM
            i = 0;
            pos = this->map.h(newElement.first, i);
            while (this->map.T[pos].key != -1 && this->map.T[pos].key != DELETE) {
                i++;
                pos = this->map.h(newElement.first, i);
            }
            /// inseram elementele
            this->map.T[pos].key = newElement.first;
            this->map.T[pos].values[this->index] = newElement.second;
        } else {
            /// cand stergem doar valoarea
            int i = 0;
            int pos = this->map.h(currentKey, i);
            while (this->map.T[pos].key != currentKey) {
                i++;
                pos = this->map.h(currentKey, i);
            }
            /// actoalizam SMM
            this->map.T[pos].values[this->index] = newElement.second;
        }
        /// actualizam array ul iteratorului
        this->arr[this->key_index].values[this->index] = newElement.second;

        return;
    }
    throw exception();
}


