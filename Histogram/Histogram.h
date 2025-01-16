#pragma once

#include "../Sequences/Sequence.h"
#include "../Sorting/SortingAlgorithms.h"
#include "../Tests/Person.h"
#include "../Hash/HashTable.h"

void InterfaceForHistogramPeople();
void InterfaceForHistogramNumber(int change);

template <typename U, typename V, typename Getter>
void PrintHistogram(Sequence<U>& seq, Getter getter, const std::string& label) {
    int count = seq.GetLength();

    if (count == 0) {
        std::cout << label << " Гистограма: Нет доступа к данным.\n";
        return;
    }

    V first_value = getter(seq.GetElement(0));
    V max_value = first_value;
    V min_value = first_value;

    for (int i = 1; i < count; ++i) {
        V value = getter(seq.GetElement(i));
        if (value > max_value) {
            max_value = value;
        }
        if (value < min_value) {
            min_value = value;
        }
    }

    int interval_size = (max_value - min_value) / 10 + 1;

    std::cout << label << " Гистограма:\n";
    for (V i = min_value; i < max_value; i += interval_size) {
        std::cout.width(2);
        std::cout << i << " - " << (i + interval_size) << " | ";

        bool found = false;

        for (int j = 0; j < count; ++j) {
            V value = getter(seq.GetElement(j));
            if (value >= i && value < (i + interval_size)) {
                std::cout << "x ";
                found = true;
            }
        }

        if (!found) {
            std::cout << "- ";
        }

        std::cout << "\n";
    }
}


template <typename T, typename Getter>
void PrintHistogram(Sequence<T>& seq, Getter getter, const std::string& label) {
    int count = seq.GetLength();

    if (count == 0) {
        std::cout << label << " Гистограма: нет доступа к данным.\n";
        return;
    }

    T first_value = getter(seq.GetElement(0));
    T max_value = first_value;
    T min_value = first_value;

    for (int i = 1; i < count; ++i) {
        T value = getter(seq.GetElement(i));
        if (value > max_value) {
            max_value = value;
        }
        if (value < min_value) {
            min_value = value;
        }
    }

    int interval_size = (max_value - min_value) / 10 + 1;

    std::cout << label << " Гистограма:\n";
    for (int i = min_value; i < max_value; i += interval_size) {
        std::cout.width(2);
        std::cout << i << " - " << (i + interval_size) << " | ";

        bool found = false;

        for (int j = 0; j < count; ++j) {
            T value = getter(seq.GetElement(j));
            if (value >= i && value < (i + interval_size)) {
                std::cout << "=";
                found = true;
            }
        }

        if (!found) {
            std::cout << "- ";
        }

        std::cout << "\n";
    }
}
