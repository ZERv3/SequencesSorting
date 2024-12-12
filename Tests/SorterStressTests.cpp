#include <random>
#include <chrono>
#include <string>
#include "../Sequences/DynamicArray.h"
#include "../Sequences/LinkedList.h"
#include "../Sorting/SortingAlgorithms.h"

// Компаратор для целых чисел (по возрастанию)
bool AscendingInt(const int &a, const int &b) {
    return a < b;
}

// Заполнение последовательности случайными числами
template <typename T>
void FillWithRandomData(Sequence<T>& sequence, int size, int minVal, int maxVal) {
    sequence.Clear();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dist(minVal, maxVal);
    for (int i = 0; i < size; ++i) {
        sequence.PushFront(dist(gen));
    }
}

// Проверка корректности сортировки (без вывода)
template <typename T>
bool IsSorted(Sequence<T>& sequence, bool (*comparator)(const T&, const T&)) {
    int len = sequence.GetLength();
    for (int i = 1; i < len; ++i) {
        if (comparator(sequence.GetElement(i), sequence.GetElement(i - 1))) {
            return false;
        }
    }
    return true;
}

// Функция измерения времени сортировки (возвращает double в миллисекундах)
template <typename T, typename Sorter>
double MeasureSortTime(Sorter& sorter, Sequence<T>& sequence, bool (*comparator)(const T&, const T&), bool checkCorrectness = true) {
    auto start = std::chrono::high_resolution_clock::now();
    sorter.Sort(sequence, comparator);
    auto end = std::chrono::high_resolution_clock::now();

    if (checkCorrectness) {
        // Если хотите обрабатывать ошибку, можно, к примеру, бросать исключение или возвращать отрицательное значение
        if (!IsSorted(sequence, comparator)) {
            // Сортировка не корректна - в данном случае просто возвращаем -1 как признак ошибки
            return -1.0;
        }
    }

    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
}

// Ниже идут отдельные функции для каждого сортировщика.
// Каждая функция принимает:
// - dataSize: размер данных для теста
// - testRuns: количество повторов
// - minVal, maxVal: диапазон значений для генерации данных
// - Использует DynamicArray (при желании можно переключить на LinkedList)
// Возвращает среднее время работы в миллисекундах.

double RunInsertionSortPerformanceTest(int dataSize, int testRuns = 5, int minVal = 0, int maxVal = 1000000) {
    InsertionSorter<int> sorter;
    DynamicArray<int> sequence;
    double total = 0.0;

    for (int i = 0; i < testRuns; ++i) {
        FillWithRandomData(sequence, dataSize, minVal, maxVal);
        double timeMs = MeasureSortTime(sorter, sequence, AscendingInt, true);
        if (timeMs < 0) return -1.0; // Ошибка сортировки
        total += timeMs;
    }

    return total / testRuns;
}

double RunMergeSortPerformanceTest(int dataSize, int testRuns = 5, int minVal = 0, int maxVal = 1000000) {
    MergeSorter<int> sorter;
    DynamicArray<int> sequence;
    double total = 0.0;

    for (int i = 0; i < testRuns; ++i) {
        FillWithRandomData(sequence, dataSize, minVal, maxVal);
        double timeMs = MeasureSortTime(sorter, sequence, AscendingInt, true);
        if (timeMs < 0) return -1.0;
        total += timeMs;
    }

    return total / testRuns;
}

double RunQuickSortPerformanceTest(int dataSize, int testRuns = 5, int minVal = 0, int maxVal = 1000000) {
    QuickSorter<int> sorter;
    DynamicArray<int> sequence;
    double total = 0.0;

    for (int i = 0; i < testRuns; ++i) {
        FillWithRandomData(sequence, dataSize, minVal, maxVal);
        double timeMs = MeasureSortTime(sorter, sequence, AscendingInt, true);
        if (timeMs < 0) return -1.0;
        total += timeMs;
    }

    return total / testRuns;
}

double RunBubbleSortPerformanceTest(int dataSize, int testRuns = 5, int minVal = 0, int maxVal = 1000000) {
    BubbleSorter<int> sorter;
    DynamicArray<int> sequence;
    double total = 0.0;

    for (int i = 0; i < testRuns; ++i) {
        FillWithRandomData(sequence, dataSize, minVal, maxVal);
        double timeMs = MeasureSortTime(sorter, sequence, AscendingInt, true);
        if (timeMs < 0) return -1.0;
        total += timeMs;
    }

    return total / testRuns;
}

double RunPancakeSortPerformanceTest(int dataSize, int testRuns = 5, int minVal = 0, int maxVal = 1000000) {
    PancakeSorter<int> sorter;
    DynamicArray<int> sequence;
    double total = 0.0;

    for (int i = 0; i < testRuns; ++i) {
        FillWithRandomData(sequence, dataSize, minVal, maxVal);
        double timeMs = MeasureSortTime(sorter, sequence, AscendingInt, true);
        if (timeMs < 0) return -1.0;
        total += timeMs;
    }

    return total / testRuns;
}