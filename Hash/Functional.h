#pragma once

#include <string>
//Custom Hash Function [CHF] Namespace
namespace chf {
    //Int Hash Function
    inline int hash(const unsigned int index, unsigned int capacity){
        return index%capacity;
    }

    //String Hash Function
    inline int hash(const std::string& word, unsigned int capacity){
        return (word.size())%capacity;
    }

    inline bool isEqual(const int& x, const int& y){
        return x==y;
    }
    
    inline bool isEqual(const std::string& x, const std::string& y){
        return x==y;
    }
}
