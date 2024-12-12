#pragma once

#include "../Sequences/Sequence.h"

// Компаратор для целых чисел (по возрастанию)
bool AscendingInt(const int &a, const int &b);

// Заполнение последовательности случайными числами
template <typename T>
void FillWithRandomData(Sequence<T>& sequence, int size, int minVal, int maxVal);

// Проверка корректности сортировки
template <typename T>
bool IsSorted(const Sequence<T>& sequence, bool (*comparator)(const T&, const T&));

// Измерение времени сортировки (в миллисекундах)
template <typename T, typename Sorter>
double MeasureSortTime(Sorter& sorter, Sequence<T>& sequence, bool (*comparator)(const T&, const T&), bool checkCorrectness = true);

// Отдельные функции для выполнения тестов производительности
double RunInsertionSortPerformanceTest(int dataSize, int testRuns = 5, int minVal = 0, int maxVal = 1000000);
double RunMergeSortPerformanceTest(int dataSize, int testRuns = 5, int minVal = 0, int maxVal = 1000000);
double RunQuickSortPerformanceTest(int dataSize, int testRuns = 5, int minVal = 0, int maxVal = 1000000);
double RunBubbleSortPerformanceTest(int dataSize, int testRuns = 5, int minVal = 0, int maxVal = 1000000);
double RunPancakeSortPerformanceTest(int dataSize, int testRuns = 5, int minVal = 0, int maxVal = 1000000);