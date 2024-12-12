#pragma once

#include <string>
#include "../Sequences/Sequence.h"
#include "../Sequences/DynamicArray.h"
#include "../Sorting/SortingAlgorithms.h"

// Компараторы для сортировки чисел
inline bool AscendingInt(const int &a, const int &b);
inline bool DescendingInt(const int &a, const int &b);

// Функция загрузки чисел из файла в последовательность
bool LoadIntegersFromFile(const std::string& filename, Sequence<int>& sequence);

// Функция сохранения чисел из последовательности в файл
bool SaveIntegersToFile(const std::string& filename, Sequence<int>& sequence);

// Меню для сортировки чисел
void RunIntegerSortingMenu();