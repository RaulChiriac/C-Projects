#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

    int key_index;
    int index;
    struct DD {
        TKey key;
        TValue* values;
        int valueCount; /// Um die Anzahl der Werte für jeden Schlüssel zu verfolgen
    };
    DD* arr; /// Das Array, das die Schlüssel und Werte enthält
    int size_arr;


public:
	void first();
	void next();
    void modifyCurrent(TElem newElement);
	bool valid() const;
   	TElem getCurrent() const;
};

