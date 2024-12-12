#pragma once

#include "Person.h"
#include "../Sequences/Sequence.h"

// Объявление унифицированной функции для тестирования сортировок
template <typename T, typename Sorter>
void TestSort(Sorter& sorter, Sequence<T>& sequence, bool (*comparator)(const T&, const T&));

// Объявление функции для заполнения последовательности значениями
void FillSequence(Sequence<int>& sequence);

// Объявление функции для заполнения последовательности значениями
void FillPersonSequence(Sequence<Person>& sequence);

// Объявление функции для тестирования сортировок с различными сортировщиками и компараторами
void RunSorterFunctionalTests();