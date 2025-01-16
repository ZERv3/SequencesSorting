#include <random>
#include <chrono>
#include <string>
#include <cmath>
#include "../Sequences/DynamicArray.h"
#include "../Sequences/LinkedList.h"
#include "../Sorting/SortingAlgorithms.h"

// Компаратор для целых чисел (по возрастанию)
bool AscendingInt(const int &a, const int &b) {
    return a < b;
}

// Заполнение последовательности случайными числами
// Предполагается, что класс Sequence<T> имеет методы Clear() и PushFront(T)
template <typename T>
void FillWithRandomData(Sequence<T>& sequence, int size, int minVal, int maxVal, double sortedPercentage = 0.0, bool smallChange = false) {
    // Очистка последовательности перед заполнением
    sequence.Clear();

    // Ограничение значения sortedPercentage в диапазоне [0, 100]
    if (sortedPercentage < 0.0) sortedPercentage = 0.0;
    if (sortedPercentage > 100.0) sortedPercentage = 100.0;

    // Определение количества элементов, которые будут отсортированы
    int sortedSize = static_cast<int>((sortedPercentage / 100.0) * size);
    sortedSize = std::min(sortedSize, size); // Убедимся, что не превышаем общий размер

    // Инициализация генератора случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dist(minVal, maxVal);

    // Генерация отсортированной части последовательности
    if (sortedSize > 0) {
        int range = maxVal - minVal + 1;

        if (range >= sortedSize) {
            // Если диапазон достаточен для уникальных значений, генерируем отсортированные уникальные значения
            // Начнем с minVal и увеличиваем на 1 для каждого следующего элемента
            // При этом не превышаем maxVal
            // Добавляем элементы в обратном порядке, поскольку используем PushFront

            // Вычисляем количество уникальных значений, которое можно использовать
            int uniqueValues = std::min(range, sortedSize);

            // Начальное значение
            T current = minVal;

            for (int i = 0; i < uniqueValues; ++i) {
                sequence.PushFront(current);
                ++current;
            }

            // Если sortedSize > uniqueValues, добавляем дополнительные уникальные значения или повторяем существующие
            for (int i = uniqueValues; i < sortedSize; ++i) {
                if (current > maxVal) {
                    current = minVal; // Циклически возвращаемся к minVal
                }
                sequence.PushFront(current);
                ++current;
            }

            // В итоге отсортированная часть будет отсортирована по возрастанию
        }
        else {
            // Если диапазон меньше необходимого количества уникальных элементов,
            // распределяем повторения равномерно

            // Общее количество уникальных значений
            int uniqueValues = range;

            // Базовое количество повторений для каждого значения
            int baseReps = sortedSize / uniqueValues;

            // Остаток, который нужно распределить среди первых 'extra' значений
            int extra = sortedSize % uniqueValues;

            // Добавляем значения от maxVal к minVal, чтобы при использовании PushFront порядок был minVal -> maxVal
            for (int val = minVal; val <= maxVal; ++val) {
                // Определяем количество повторений для текущего значения
                int reps = baseReps + ( (maxVal - val) < extra ? 1 : 0 );

                for (int r = 0; r < reps; ++r) {
                    sequence.PushFront(static_cast<T>(val));
                }
            }

            // В итоге отсортированная часть будет содержать равномерные повторения значений
        }
    }

    // Генерация оставшейся части случайных элементов
    int randomSize = size - sortedSize;
    for (int i = 0; i < randomSize; ++i) {
        T randomValue = dist(gen);
        sequence.PushFront(randomValue);
    }
    
    if(smallChange)
    {
        for (int i = static_cast<int>(size*0.1) + 1; i < size/2; i+= static_cast<int>(size*0.1) + 1) {
            sequence.Swap(sequence.GetElement(i), sequence.GetElement(size-i));
        }
    }
    
    // Обратите внимание: если последовательность должна иметь отсортированную часть в начале,
    // а затем случайные элементы, использование PushFront приведет к тому, что отсортированная часть будет в конце.
    // В этом случае, возможно, имеет смысл использовать PushBack, если он доступен.
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
        if (!IsSorted(sequence, comparator)) {
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

double RunInsertionSortPerformanceTest(int dataSize, int testRuns = 5, int minVal = 0, int maxVal = 1000000,double ratio = 0.0, bool smallChange = false) {
    InsertionSorter<int> sorter;
    DynamicArray<int> sequence;
    double total = 0.0;

    for (int i = 0; i < testRuns; ++i) {
        FillWithRandomData(sequence, dataSize, minVal, maxVal, ratio, smallChange);
        double timeMs = MeasureSortTime(sorter, sequence, AscendingInt, true);
        if (timeMs < 0) return -1.0; // Ошибка сортировки
        total += timeMs;
    }

    return total / testRuns;
}

double RunMergeSortPerformanceTest(int dataSize, int testRuns = 5, int minVal = 0, int maxVal = 1000000,  double ratio = 0.0, bool smallChange = false) {
    MergeSorter<int> sorter;
    DynamicArray<int> sequence;
    double total = 0.0;

    for (int i = 0; i < testRuns; ++i) {
        FillWithRandomData(sequence, dataSize, minVal, maxVal, ratio, smallChange);
        double timeMs = MeasureSortTime(sorter, sequence, AscendingInt, true);
        if (timeMs < 0) return -1.0;
        total += timeMs;
    }

    return total / testRuns;
}

double RunQuickSortPerformanceTest(int dataSize, int testRuns = 5, int minVal = 0, int maxVal = 1000000,  double ratio = 0.0, bool smallChange = false) {
    QuickSorter<int> sorter;
    DynamicArray<int> sequence;
    double total = 0.0;

    for (int i = 0; i < testRuns; ++i) {
        FillWithRandomData(sequence, dataSize, minVal, maxVal, ratio, smallChange);
        double timeMs = MeasureSortTime(sorter, sequence, AscendingInt, true);
        if (timeMs < 0) return -1.0;
        total += timeMs;
    }

    return total / testRuns;
}

double RunBubbleSortPerformanceTest(int dataSize, int testRuns = 5, int minVal = 0, int maxVal = 1000000,  double ratio = 0.0, bool smallChange = false) {
    BubbleSorter<int> sorter;
    DynamicArray<int> sequence;
    double total = 0.0;

    for (int i = 0; i < testRuns; ++i) {
        FillWithRandomData(sequence, dataSize, minVal, maxVal, ratio, smallChange);
        double timeMs = MeasureSortTime(sorter, sequence, AscendingInt, true);
        if (timeMs < 0) return -1.0;
        total += timeMs;
    }

    return total / testRuns;
}
