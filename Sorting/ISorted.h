#pragma once
#include "../Sequences/Sequences.h"

template <class T>
class ISorter {
public:
    virtual void Sort(Sequence<T>* sequence) = 0;

    virtual ~ISorter() {}
};


/*
template <class T>
class ISorted {
public:
   // virtual void InsertionSort(Sequence<T>* sequence) = 0;
    //virtual void QuickSort(Sequence<T>* sequence) = 0;
    //virtual void BubbleSorter(Sequence<T>* sequence) = 0;
    virtual ~ISorted() {}
};
*/

//название плохое ,поменять
// должен быть один метод название отсортировать и у него должно быть н наследников по числу реализуемых алгоритмов
// избавиться от копипаста в интерфейс
//обязан включить sequence/ h компиляция не может зависить от порядка включения файлов
//если передать nullptr in isorted = segmentation fault защита
// по умолчанию передается константная ссылка в
//надо передавать ссылка, может сломаться адрес