#pragma once

#include "../Hash/HashTable.h"
#include "../Hash/IDictionary.h"
#include <iostream>

template <typename TKey, typename TValue>
void ViewHT(const HashTable<TKey, TValue>& HT){
    std::cout << HT;
}

template <typename TKey, typename TValue>
void ViewHT_Items(const HashTable<TKey, TValue>& HT){
    auto items = HT.GetItems();
    std::cout << items;
}

template <typename TKey, typename TValue>
void ViewIDictionary(const IDictionary<TKey, TValue>& dict){
    auto hashTable = dict.GetHT();
    std::cout << hashTable;
}
