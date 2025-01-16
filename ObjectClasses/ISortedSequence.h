#pragma once

#include <iostream>

#include "../Sequences/Sequence.h"
#include "../Histogram/Histogram.h"

// Шаблонный класс ISortedSequence для работы с отсортированными последовательностями
template <typename T>
class ISortedSequence : public Sequence<T> {
private:
    LinkedList<T> sequence; // Хранилище последовательности
    bool (*comp)(const T& first, const T& second); // Указатель на функцию сравнения

    // Метод сортировки последовательности с использованием QuickSort
    void sortSequence() {
        QuickSorter<T> sorter;
        sorter.Sort(sequence, comp); // Сортировка с использованием переданной функции сравнения
    }

public:
    // Конструктор по умолчанию
    ISortedSequence() : comp(nullptr) {}

    // Конструктор, принимающий входную последовательность и функцию сравнения
    template <typename Iterable>
    ISortedSequence(Iterable& inputSequence, bool (*precedes)(const T& first, const T& second)) {
        comp = precedes; // Устанавливаем функцию сравнения
        int length = inputSequence.GetLength();
        for (int i = 0; i < length; ++i) {
            sequence.PushFront(inputSequence.GetElement(i)); // Добавляем элементы из входной последовательности
        }
        sortSequence(); // Сортируем после добавления всех элементов
    }

    // Метод добавления элемента с автоматической сортировкой
    void PushFront(T element) override {
        sequence.PushFront(element); // Добавляем элемент в последовательность
        sortSequence(); // Пересортировка после добавления
    }
    
    void PushBack(T element) override {
        sequence.PushBack(element);
        sortSequence();
    }
    
    void Insert(T item, int index) override {
        sequence.Insert(item, index);
        sortSequence();
    }

    // Возвращает количество элементов в последовательности
    int GetLength() override {
        return sequence.GetLength();
    }

    // Возвращает элемент по индексу
    T& GetElement(int index) override {
        return sequence.GetElement(index);
    }

    // Очищает последовательность
    void Clear() override {
        sequence.Clear();
    }

    // Возвращает первый элемент последовательности
    T& GetHead() override {
        return sequence.GetHead();
    }

    // Возвращает последний элемент последовательности
    T& GetTail() override {
        return sequence.GetTail();
    }
    
    void Concat(Sequence<T>* list) override {
        sequence.Concat(list);
        sortSequence();
    }
    
    void Set(T item, int index) override {
        sequence.Set(item, index);
        sortSequence();
    }
    
    void Swap(T& a, T& b) override {
        sequence.Swap(a,b);
        sortSequence();
    }
    
    ISortedSequence<T>* GetSubsequence(int startIndex, int endIndex) override {
        // Получаем подпоследовательность из исходного списка
        LinkedList<T>* subsequence = sequence.GetSubsequence(startIndex, endIndex);

        // Создаем новый объект ISortedSequence<T> на основе подпоследовательности
        ISortedSequence<T>* sortedSubsequence = new ISortedSequence<T>(*subsequence, comp);

        delete subsequence; // Удаляем временный объект, чтобы избежать утечек памяти
        return sortedSubsequence;
    }
    
    typename Sequence<T>::Iterator* ToBegin() override {
        return sequence.ToBegin();
    }
    
    typename Sequence<T>::Iterator* ToEnd() override {
        return sequence.ToEnd();
    }
    
    // Выводит элементы последовательности на экран
    void Print() {
        for (int i = 0; i < sequence.GetLength(); ++i) {
            std::cout << sequence[i] << " "; // Печать каждого элемента последовательности
        }
        std::cout << std::endl; // Завершаем строку вывода
    }
};
