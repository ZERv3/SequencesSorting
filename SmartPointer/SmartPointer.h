#pragma once

#include <optional>

template <typename T>
class SmrtPtr {
private:
    T* ptr;
    int* ref_count;

    void release(){
        if (--(*ref_count) == 0){
            delete ptr;
            delete ref_count;
        }
    }

public:
    // Конструктор
    explicit SmrtPtr(T* p = nullptr) : ptr(p), ref_count(new int(1)) {}

    // Деструктор
    ~SmrtPtr(){
        release();
    }

    // Копирование
    SmrtPtr(const SmrtPtr<T>& other) : ptr(other.ptr), ref_count(other.ref_count){
        (*ref_count)++;
    }

    // Перемещение
    SmrtPtr(SmrtPtr<T>&& other) noexcept : ptr(other.ptr), ref_count(other.ref_count){
        other.ptr = nullptr;
        other.ref_count = new int(1);
    }

    // Копирование
    // TODO: исправить условие на ref_count на просто release(); - DONE
    SmrtPtr& operator=(const SmrtPtr<T>& other){
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            (*ref_count)++;
        }
        return *this;
    }

    // Перемещение
    SmrtPtr& operator=(SmrtPtr<T>&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            other.ptr = nullptr;
            other.ref_count = new int(1);
        }
        return *this;
    }


    // TODO: optional либо выброс исключения для nullptr - DONE
    const T& operator*() const {
        if (!ptr) {
            throw std::runtime_error("Dereferencing nullptr!");
        }
        return *ptr;
    }

    T& operator*() {
        if (!ptr) {
            throw std::runtime_error("Dereferencing nullptr!");
        }
        return *ptr;
    }

    const T* operator->() const {
        if (!ptr) {
            throw std::runtime_error("Accessing nullptr!");
        }
        return ptr;
    }

    T* operator->() {
        if (!ptr) {
            throw std::runtime_error("Accessing nullptr!");
        }
        return ptr;
    }

    const T* get() const {
        return ptr; // Для get можно не выбрасывать исключение
    }

    T* get() {
        return ptr; // Для get можно не выбрасывать исключение
    }

    int getRefCount() const {
        return *ref_count;
    }
};


