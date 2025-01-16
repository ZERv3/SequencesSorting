#pragma once

#include "../Hash/Functional.h"

template <typename T>
class Extractor {
private:
    unsigned int index;
    T value;
public:
    Extractor() : index(0), value(T()) {}
    Extractor(int idx, T val) : index(idx), value(val) {}
    
    int GetIndex() const {return this->index;}
    T GetValue() const {return this->value;}
    
    bool operator==(const Extractor<T>& other){
        return (this->index == other.GetIndex() && this->value == other.GetValue());
    }
    
    friend std::ostream& operator<<(std::ostream& outStream, const Extractor<T>& extractor) {
        outStream << "EXTRACTOR:("
            << extractor.GetIndex() << " , "
            << extractor.GetValue() << ")";
        return outStream;
    }
};


#include <iostream>

namespace chf{
    template <typename T>
    inline unsigned int hash(const Extractor<T> extractedObject, unsigned int capacity){
        int index = extractedObject.GetIndex();
        return hash(index, capacity);
    }
}
