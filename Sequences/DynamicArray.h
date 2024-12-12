#pragma once

#include <iostream>
#include "Sequence.h"

template <class T>
class DynamicArray : public Sequence<T> {
private:
    T* data;
    int size;

    void Resize(int newSize) {
        T* newData = new T[newSize];
        int minSize = (newSize < size) ? newSize : size;
        for (int i = 0; i < minSize; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        size = newSize;
    }

public:
    class DynamicArrayIterator : public Sequence<T>::Iterator {
    private:
        T* current;

    public:
        DynamicArrayIterator(T* current) : current(current) {}
        bool operator==(const typename Sequence<T>::Iterator& other) const override {
            const auto* otherIterator = dynamic_cast<const DynamicArrayIterator*>(&other);
            return otherIterator && current == otherIterator->current;
        }
        bool operator!=(const typename Sequence<T>::Iterator& other) const override {
            return !(*this == other);
        }
        T& operator*() override {
            return *current;
        }
        typename Sequence<T>::Iterator& operator++() override {
            current++;
            return *this;
        }
    };

    typename Sequence<T>::Iterator* ToBegin() override {
        return new DynamicArrayIterator(data);
    }

    typename Sequence<T>::Iterator* ToEnd() override {
        return new DynamicArrayIterator(data + size);
    }

    DynamicArray() : size(0), data(nullptr) {}

    DynamicArray(T* items, int size) {
        this->size = size;
        data = new T[size];
        for (int i = 0; i < size; ++i) {
            Set(items[i], i);
        }
    }

    DynamicArray(int size) : size(size), data(new T[size]) {}

    DynamicArray(const DynamicArray<T>& dynamicArray) {
        size = dynamicArray.size;
        data = new T[size];
        for (int i = 0; i < size; ++i) {
            Set(dynamicArray.data[i], i);
        }
    }

    ~DynamicArray() {
        delete[] data;
    }

    T& operator[](int index) {
        return data[index];
    }

    T& GetHead() override {
        return GetElement(0);
    }

    T& GetTail() override {
        return GetElement(size - 1);
    }

    T& GetElement(int index) override {
        return data[index];
    }

    void Swap(T& a, T& b) override {
        T temp = a;
        a = b;
        b = temp;
    }

    void Set(T item, int index) override {
        data[index] = item;
    }

    DynamicArray<T>* GetSubsequence(int startIndex, int endIndex) override {
        int length = (endIndex > size) ? size - startIndex : endIndex - startIndex + 1;
        T* items = new T[length];
        for (int i = 0; i < length; i++) {
            items[i] = GetElement(startIndex + i);
        }
        return new DynamicArray<T>(items, length);
    }

    int GetLength() override {
        return size;
    }

    void PushFront(T data) override {
        Insert(data, size);
    }

    void PushBack(T data) override {
        Insert(data, 0);
    }

    void Insert(T data, int index) override {
        Resize(size + 1);
        for (int i = size - 1; i > index; i--) {
            Set(GetElement(i - 1), i);
        }
        Set(data, index);
    }

    void Concat(Sequence<T>* dynamicArray) override {
        for (int i = 0; i < dynamicArray->GetLength(); i++) {
            PushFront(dynamicArray->GetElement(i));
        }
    }

    // void Print() const {
    //     std::cout << "Elements in the array: ";
    //     for (int i = 0; i < size; i++) {
    //         std::cout << data[i] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    void Clear() override{
        delete[] data;
        data = nullptr;
        size = 0;
    }
};