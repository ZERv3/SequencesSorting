#include "../Sorting/SortingAlgorithms.h"
#include "Person.h"
#include "../Sequences/Sequence.h"
#include "../Sequences/DynamicArray.h"
#include <iostream>
#include <cassert>

// Унифицированная функция для тестирования сортировок
template <typename T, typename Sorter>
void TestSort(Sorter& sorter, Sequence<T>& sequence, bool (*comparator)(const T&, const T&)) {
    sorter.Sort(sequence, comparator);

    for (int i = 1; i < sequence.GetLength(); ++i) {
        assert(!comparator(sequence.GetElement(i), sequence.GetElement(i - 1)));
    }
    std::cout << "Test passed." << std::endl;
}

// Функция для заполнения последовательности значениями
void FillSequence(Sequence<int>& sequence) {
    sequence.Clear();
    sequence.PushFront(5);
    sequence.PushFront(3);
    sequence.PushFront(8);
    sequence.PushFront(1);
    sequence.PushFront(6);
}

void FillPersonSequence(Sequence<Person>& sequence) {
    sequence.Clear();
    sequence.PushFront(Person(1, "Alice", "Smith", 1990, 1.65, 55));
    sequence.PushFront(Person(2, "Bob", "Johnson", 1985, 1.80, 75));
    sequence.PushFront(Person(3, "Charlie", "Brown", 1992, 1.75, 70));
}

// Функция для тестирования сортировок с различными сортировщиками и компараторами
void RunSorterFunctionalTests() {
    InsertionSorter<int> insertionSorter;
    MergeSorter<int> mergeSorter;
    QuickSorter<int> quickSorter;
    BubbleSorter<int> bubbleSorter;
    PancakeSorter<int> pancakeSorter;

    DynamicArray<int> sequence(5);
    FillSequence(sequence);

    // Тестирование сортировок с последовательностью чисел
    std::cout << "Testing Insertion Sort with integers..." << std::endl;
    TestSort(insertionSorter, sequence, AscendingInt);

    std::cout << "Testing Merge Sort with integers..." << std::endl;
    FillSequence(sequence);
    TestSort(mergeSorter, sequence, AscendingInt);

    std::cout << "Testing Quick Sort with integers..." << std::endl;
    FillSequence(sequence);
    TestSort(quickSorter, sequence, AscendingInt);

    std::cout << "Testing Bubble Sort with integers..." << std::endl;
    FillSequence(sequence);
    TestSort(bubbleSorter, sequence, AscendingInt);

    std::cout << "Testing Pancake Sort with integers..." << std::endl;
    FillSequence(sequence);
    TestSort(pancakeSorter, sequence, AscendingInt);

    // Тестирование сортировки объектов Person
    DynamicArray<Person> personSequence(3);

    std::cout << "Testing Merge Sort with Person objects by first name..." << std::endl;
    FillPersonSequence(personSequence);
    MergeSorter<Person> personMergeSorter;
    TestSort(personMergeSorter, personSequence, CompareFirstName);

    std::cout << "Testing Bubble Sort with Person objects by first name..." << std::endl;
    FillPersonSequence(personSequence);
    BubbleSorter<Person> personBubbleSorter;
    TestSort(personBubbleSorter, personSequence, CompareFirstName);

    std::cout << "Testing Pancake Sort with Person objects by first name..." << std::endl;
    FillPersonSequence(personSequence);
    PancakeSorter<Person> personPancakeSorter;
    TestSort(personPancakeSorter, personSequence, CompareFirstName);

    std::cout << "Testing Quick Sort with Person objects by first name..." << std::endl;
    FillPersonSequence(personSequence);
    QuickSorter<Person> personQuickSorter;
    TestSort(personQuickSorter, personSequence, CompareFirstName);

    std::cout << "All sorting tests passed successfully!" << std::endl;
}
