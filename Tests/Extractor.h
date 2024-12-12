#pragma once

template <typename T>
struct Extractor {
    int index;
    T value;
    Extractor() : index(0), value(T()) {} // Add a default constructor
    Extractor(int idx, T val) : index(idx), value(val) {}
    Extractor(const Extractor& other) : index(other.index), value(other.value) {}
};
