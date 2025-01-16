#pragma once

#include "ISorter.h"

// Сортировка вставками
template<class T>
class InsertionSorter : public ISorter<T> {
public:
    void Sort(Sequence<T> &sequence, bool (*comparator)(const T &first, const T &second)) override {
        int n = sequence.GetLength();
        for (int i = 1; i < n; ++i) {
            T key = sequence.GetElement(i);
            int j = i - 1;
            while (j >= 0 && comparator(key, sequence.GetElement(j))) {
                sequence.Set(sequence.GetElement(j), j + 1);
                j--;
            }
            sequence.Set(key, j + 1);
        }
    }
};

// Сортировка слиянием
template<class T>
class MergeSorter : public ISorter<T> {
private:
    void Merge(Sequence<T> &sequence, int left, int mid, int right, bool (*comparator)(const T &first, const T &second)) {
        int n1 = mid - left + 1; //левая длина
        int n2 = right - mid; //правая длина

        //Исправить вместо выделения памяти -> индексы
//        Sequence<T>* leftSeq = sequence.GetSubsequence(left, mid);
//        Sequence<T>* rightSeq = sequence.GetSubsequence(mid + 1, right);

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (!comparator(sequence.GetElement(mid + 1 + j), sequence.GetElement(left + i))) {
                sequence.Set(sequence.GetElement(left + i), k++);
                i++;
            } else {
                sequence.Set(sequence.GetElement(mid + 1 + j), k++);
                j++;
            }
        }

        while (i < n1) {
            sequence.Set(sequence.GetElement(left + i), k++);
            i++;
        }

        while (j < n2) {
            sequence.Set(sequence.GetElement(mid + 1 + j), k++);
            j++;
        }

//        delete leftSeq;
//        delete rightSeq;
    }

    void MergeSort(Sequence<T> &sequence, int left, int right, bool (*comparator)(const T &first, const T &second)) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            MergeSort(sequence, left, mid, comparator);
            MergeSort(sequence, mid + 1, right, comparator);
            Merge(sequence, left, mid, right, comparator);
        }
    }

public:
    void Sort(Sequence<T> &sequence, bool (*comparator)(const T &first, const T &second)) override {
        MergeSort(sequence, 0, sequence.GetLength() - 1, comparator);
    }
};

// Быстрая сортировка (Quicksort)
template<class T>
class QuickSorter : public ISorter<T> {
private:
    int Partition(Sequence<T> &sequence, int low, int high, bool (*comparator)(const T &first, const T &second)) {
        T pivot = sequence.GetElement(high);
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (comparator(sequence.GetElement(j), pivot)) {
                i++;
                T temp = sequence.GetElement(i);
                sequence.Set(sequence.GetElement(j), i);
                sequence.Set(temp, j);
            }
        }
        T temp = sequence.GetElement(i + 1);
        sequence.Set(sequence.GetElement(high), i + 1);
        sequence.Set(temp, high);
        return i + 1;
    }

    void QuickSort(Sequence<T> &sequence, int low, int high, bool (*comparator)(const T &first, const T &second)) {
        if (low < high) {
            int pi = Partition(sequence, low, high, comparator);
            QuickSort(sequence, low, pi - 1, comparator);
            QuickSort(sequence, pi + 1, high, comparator);
        }
    }

public:
    void Sort(Sequence<T> &sequence, bool (*comparator)(const T &first, const T &second)) override {
        QuickSort(sequence, 0, sequence.GetLength() - 1, comparator);
    }
};

// Пузырьковая сортировка (Bubblesort)
template<class T>
class BubbleSorter : public ISorter<T> {
public:
    void Sort(Sequence<T> &sequence, bool (*comparator)(const T &first, const T &second)) override {
        int n = sequence.GetLength();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (comparator(sequence.GetElement(j + 1), sequence.GetElement(j))) {
                    T temp = sequence.GetElement(j);
                    sequence.Set(sequence.GetElement(j + 1), j);
                    sequence.Set(temp, j + 1);
                }
            }
        }
    }
};
