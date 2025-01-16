#pragma once
#include "../Sequences/Sequence.h"
#include "../Hash/Functional.h"

template <typename T>
class ISet : public Sequence<T> {
private:
    LinkedList<T> sequence; // Внутреннее хранилище множества, основанное на LinkedList

    // Метод для удаления дубликатов из последовательности
    void RemoveDuplicates() {
        LinkedList<T> unique_elements;  // Временный список для уникальных элементов
        LinkedList<T> seen_elements;    // Временный список для отслеживания добавленных элементов

        // Проход по всем элементам последовательности
        for (int i = 0; i < sequence.GetLength(); ++i) {
            T value = sequence.GetElement(i);
            // Проверяем, содержится ли элемент в списке уникальных
            bool is_unique = true;
            for (int j = 0; j < seen_elements.GetLength(); ++j) {
                if (chf::isEqual(seen_elements.GetElement(j), value)) {
                    is_unique = false;
                    break;
                }
            }

            if (is_unique) {
                unique_elements.PushFront(value);
                seen_elements.PushFront(value);
            }
        }

        sequence.Clear(); // Очистка текущей последовательности

        // Перезапись последовательности уникальными элементами
        for (int i = 0; i < unique_elements.GetLength(); ++i) {
            sequence.Insert(unique_elements.GetElement(i), i);
        }
    }

public:
    // Конструктор по умолчанию
    ISet() {}

    // Конструктор, принимающий итеративный ввод (например, последовательности)
    template <typename Iterable>
    ISet(Iterable& inputSequence) {
        // Копирование элементов из inputSequence в LinkedList
        int length = inputSequence.GetLength();
        for (int i = 0; i < length; ++i) {
            PushFront(inputSequence.GetElement(i));
        }

        // Удаление дубликатов для обеспечения уникальности элементов
        RemoveDuplicates();
    }

    // Добавление элемента в множество
    void PushFront(T element) override {
        // Проверяем, существует ли элемент уже в множестве
        for (int i = 0; i < sequence.GetLength(); ++i) {
            if (chf::isEqual(sequence.GetElement(i) , element)) {
                return; // Элемент уже существует, не добавляем его
            }
        }

        // Добавляем элемент, если его еще нет
        sequence.PushFront(element);
    }
    // Добавление элемента в множество
    void PushBack(T element) override {
        // Проверяем, существует ли элемент уже в множестве
        for (int i = 0; i < sequence.GetLength(); ++i) {
            if (chf::isEqual(sequence.GetElement(i), element)) {
                return; // Элемент уже существует, не добавляем его
            }
        }

        // Добавляем элемент, если его еще нет
        sequence.PushBack(element);
    }

    // Очистка множества
    void Clear() override {
        sequence.Clear();
    }
    
    void Set(T item, int index) override {
        sequence.Set(item, index);
    }
    
    ISet<T>* GetSubsequence(int startIndex, int endIndex) override {
        // Создаем новый объект множества
        ISet<T>* subset = new ISet<T>();

        // Получаем элементы подпоследовательности из внутреннего списка
        LinkedList<T>* subsequence = sequence.GetSubsequence(startIndex, endIndex);

        // Добавляем элементы в новое множество
        for (int i = 0; i < subsequence->GetLength(); ++i) {
            subset->PushBack(subsequence->GetElement(i));
        }

        return subset;
    }

    
    void Concat(Sequence<T>* set) override {
        sequence.Concat(set);
    }
    
    void Swap(T& a, T& b) override {
        sequence.Swap(a, b);
    }
    
    void Insert(T item, int index) override {
        sequence.Insert(item, index);
    }
    
    typename Sequence<T>::Iterator*
    ToBegin() override {
        return sequence.ToBegin();
    }
    typename Sequence<T>::Iterator*
    ToEnd() override {
        return sequence.ToEnd();
    }
//    Iterator* ToBegin() override {
//        return sequence.ToBegin();
//    }
//    
//    Iterator* ToEnd() override {
//        return sequence.ToEnd();
//    }

    // Получение первого элемента множества
    T& GetHead() override {
        return sequence.GetHead();
    }

    // Получение последнего элемента множества
    T& GetTail() override {
        return sequence.GetTail();
    }

    // Получение элемента по индексу
    T& GetElement(int index) override {
        return sequence.GetElement(index);
    }

    // Получение количества элементов в множестве
    int GetLength() override {
        return sequence.GetLength();
    }
    
    

    // Вывод элементов множества на экран
    void Print() {
        for (int i = 0; i < sequence.GetLength(); ++i) {
            std::cout << sequence.GetElement(i) << " ";
        }
        std::cout << std::endl;
    }
};
