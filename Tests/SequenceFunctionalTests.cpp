#include "../Sequences/DynamicArray.h"
#include "../Sequences/LinkedList.h"
#include <cassert>
#include <iostream>

// Функция для тестирования добавления элементов в динамический массив (DynamicArray)
void DynamicArrayPushBackTest() {
    DynamicArray<int> array;
    array.PushBack(1);
    array.PushBack(2);
    array.PushBack(3);
    assert(array.GetElement(0) == 3);
    assert(array.GetElement(1) == 2);
    assert(array.GetElement(2) == 1);
    std::cout << "TestDynamicArrayPushBack пройден." << std::endl;
}

// Функция для тестирования установки значения элемента в динамическом массиве (DynamicArray)
void DynamicArraySetTest() {
    DynamicArray<int> array;
    array.PushBack(1);
    array.PushBack(2);
    array.PushBack(3);
    array.Set(10, 1);
    assert(array.GetElement(1) == 10);
    std::cout << "TestDynamicArraySet пройден." << std::endl;
}

// Функция для тестирования получения длины динамического массива (DynamicArray)
void DynamicArrayGetLengthTest() {
    DynamicArray<int> array;
    array.PushBack(1);
    array.PushBack(2);
    array.PushBack(3);
    assert(array.GetLength() == 3);
    std::cout << "TestDynamicArrayGetLength пройден." << std::endl;
}

// Функция для тестирования добавления элементов в связный список (LinkedList)
void LinkedListPushFrontTest() {
    LinkedList<int> list;
    list.PushFront(1);
    list.PushFront(2);
    list.PushFront(3);
    assert(list.GetElement(0) == 1);
    assert(list.GetElement(1) == 2);
    assert(list.GetElement(2) == 3);
    std::cout << "TestLinkedListPushFront пройден." << std::endl;
}

// Функция для тестирования установки значения элемента в связном списке (LinkedList)
void LinkedListSetTest() {
    LinkedList<int> list;
    list.PushFront(1);
    list.PushFront(2);
    list.PushFront(3);
    list.Set(10, 1);
    assert(list.GetElement(1) == 10);
    std::cout << "TestLinkedListSet пройден." << std::endl;
}

// Функция для тестирования получения длины связного списка (LinkedList)
void LinkedListGetLengthTest() {
    LinkedList<int> list;
    list.PushFront(1);
    list.PushFront(2);
    list.PushFront(3);
    assert(list.GetLength() == 3);
    std::cout << "TestLinkedListGetLength пройден." << std::endl;
}

void RunSequenceFunctionalTests() {
    DynamicArraySetTest();
    DynamicArrayPushBackTest();
    DynamicArrayGetLengthTest();

    LinkedListPushFrontTest();
    LinkedListSetTest();
    LinkedListGetLengthTest();

    std::cout << "All sequence tests passed successfully!" << std::endl;
}

