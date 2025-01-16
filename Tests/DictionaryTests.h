#pragma once

#include "../Hash/IDictionary.h"
#include "../Cache/LRUCDictionary.h"

#include <vector>
#include <string>

// Функция для среднего времени выполнения операции "Add"
template <typename TDictionary>
double BenchmarkAdd(TDictionary& dict,
                    const std::vector<int>& keys,
                    const std::vector<int>& values);

// Функция для среднего времени выполнения операции "GetValue"
template <typename TDictionary>
double BenchmarkGetValue(TDictionary& dict,
                         const std::vector<int>& keys);

// Функция для среднего времени выполнения операции "Remove"
template <typename TDictionary>
double BenchmarkRemove(TDictionary& dict,
                       const std::vector<int>& keys);

// Вспомогательная функция для вывода результатов и их сравнения
void PrintComparison(const std::string& operationName,
                     double msPerOpDict1,
                     double msPerOpDict2);

void RunDictionaryTests(int capacity, int cacheSize);
