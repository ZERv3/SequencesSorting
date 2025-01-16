#pragma once

template <class TElement>
class IIterator
{
public:
    TElement iter;
    IIterator* next = nullptr;
    TElement GetCurrentItem()
    {
        return iter;
    }
    IIterator(TElement it) : iter(it) {}
    IIterator() {}
    ~IIterator()
    {
    }
    void init(TElement el) { iter = el; }
    bool HasNext(){
        if (this->next != nullptr)
        {
            return true;
        }
        else
            false;
    }
    TElement get(TElement el)
    {
        this->iter = el;
    }
    bool Next()
    {
        if (this->next != nullptr)
        {
            this = this->next;
            return true;
        }
        else
            false;
    }
    bool Add(TElement element)
    {
        element = iter;
        if (element)
        {return true;}
        else
            false;
    }
};
