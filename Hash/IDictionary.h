#pragma once

#include "HashTable.h"

template <typename TKey, typename TValue>
class IDictionary{
private:
    HashTable<TKey, TValue>* hashTable;
public:
    // Конструкторы
    IDictionary(int capacity) : hashTable(new HashTable<TKey, TValue>(capacity)) {}
    IDictionary() : hashTable(nullptr) {}
    
    ~IDictionary(){
        delete hashTable;
    }
    
    // Геттеры
    int GetFullness(){return this->hashTable->GetFullness();}
    int GetCapacity(){return this->hashTable->GetCapacity();}
    HashTable<TKey, TValue>& GetHT() const {return this->hashTable;}
    TValue GetValue(TKey key){return this->hashTable->GetValue(key);} //Получить значение по ключу
//    HT_Item<TKey, TValue> GetItem(TKey key){return this->hashTable->GetValue(key);}
    
//    TValue isIndexFree(TKey key){return this->HT->GetValue(key);}
    void SetHT(HashTable<TKey, TValue> HT){
        delete this->hashTable;
        this->hashTable = &HT;
    }
    bool Contains(TKey key){return hashTable->Contains(key);}
    void Add(TKey key, TValue value){this->hashTable->Add(key, value);}
    void Remove(TKey key){this->hashTable->Remove(key);}
    void Generate(){
        for (TKey i = 0; i < 10; ++i){
            this->Add(i, rand() % 256);
            ++this->hashTable->fullness;
        }
    }
};

