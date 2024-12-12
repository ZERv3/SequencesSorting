#pragma once

#include "../Sequences/Sequence.h"

template<class T>
class ISorter {
public:
    virtual void Sort(Sequence<T> &sequence, bool (*comparator)(const T &first, const T &second)) = 0;
    virtual ~ISorter() = default;
};
