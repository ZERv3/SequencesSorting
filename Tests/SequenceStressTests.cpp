#include "../Sequences/LinkedList.h"
#include "../Sequences/DynamicArray.h"
#include <chrono>

// Нагрузочный тест для DynamicArray
double DynamicArrayStressTest(int numOperations) {
    DynamicArray<int> array;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numOperations; ++i) {
        array.PushBack(i); // Добавление элементов в конец
    }

    for (int i = 0; i < numOperations / 2; ++i) {
        array.Set(i * 2, i); // Изменение значения в середине массива
    }

    for (int i = 0; i < numOperations / 10; ++i) {
        array.GetElement(i); // Чтение элементов
    }

    array.Clear(); // Очистка массива

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

// Нагрузочный тест для LinkedList
double LinkedListStressTest(int numOperations) {
    LinkedList<int> list;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numOperations; ++i) {
        list.PushBack(i); // Добавление элементов в конец
    }

    for (int i = 0; i < numOperations / 2; ++i) {
        list.Set(i * 2, i); // Изменение значения в середине списка
    }

    for (int i = 0; i < numOperations / 10; ++i) {
        list.GetElement(i); // Чтение элементов
    }

    list.Clear(); // Очистка списка

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}