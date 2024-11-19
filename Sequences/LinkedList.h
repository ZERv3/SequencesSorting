#pragma once

#include "../Sequences/Sequences.h"
#include "DynamicArray.h"

template <class T>
class LinkedList : public Sequence<T>{
private:
    struct Node{
        T data;
        Node* next;

        Node(T data, Node* next = nullptr) : data(data), next(next) {}
    };

    Node* head;
    Node* tail;
    int length;

public:
    class LinkedListIterator : public Sequence<T>::Iterator {
    private:

        Node* current;

    public:

        LinkedListIterator(Node* start) : current(start) { }

        bool operator==(const Sequence<T>::Iterator& other) const override{
            const LinkedListIterator* otherIterator = dynamic_cast<const LinkedListIterator*>(&other);
            return otherIterator && current == otherIterator->current;
        }

        bool operator!=(const Sequence<T>::Iterator& other) const override{
            return !(*this == other);
        }

        T& operator*() override{
            return current->data;
        }

        Sequence<T>::Iterator& operator++() override{
            if (current){
                current = current->next;
            }

            return *this;
        }
    };

    Sequence<T>::Iterator* ToBegin() override{
        return new LinkedListIterator(head);
    }

    Sequence<T>::Iterator* ToEnd() override{
        return new LinkedListIterator(nullptr);
    }

    LinkedList() : head(nullptr), tail(nullptr), length(0) {}

    LinkedList(T* items, int count) : head(nullptr), tail(nullptr), length(0){
        for (int i = 0; i < count; ++i){
            Append(items[i]);
        }
    }

    LinkedList(LinkedList<T>& list) : head(nullptr), tail(nullptr), length(0)
    {
        Node* current = list.head;

        while (current != nullptr)
        {
            Append(current->data);
            current = current->next;
        }
    }

    LinkedList(DynamicArray<T>& dynamicArray) : head(nullptr), tail(nullptr), length(0)
    {
        for (int i = 1; i < dynamicArray.GetLength(); i++)
        {
            Append(dynamicArray.GetElement(i));
        }
    }

    ~LinkedList()
    {
        Node* current = head;
        Node* next;

        while (current != nullptr)
        {
            next = current->next;
            delete current;
            current = next;
        }
    }

    T& GetHead() override
    {
        return head->data;
    }

    T& GetTail() override{
        return tail->data;
    }

    T&  GetElement(int index)  override{
        return GetNode(index)->data;
    }

    Node* GetNode(int index){
        Node* current = head;

        for (int i = 0; i < index; i++){
            current = current->next;
        }

        return current;
    }

    void Swap(T& a, T& b) override{
        T temp = a;
        a = b;
        b = temp;
    }

    void Insert(T value, int index){
        Node* current = head;
        for (int i = 0; i < index; i++){
            current = current->next;
        }
        current->data = value;
    }

    LinkedList<T>* GetSubsequence(int startIndex, int endIndex) override{
        if (endIndex >= length){
            endIndex = length - 1;
        }

        LinkedList<T>* sublist = new LinkedList<T>();
        Node* current = head;

        for (int i = 0; i <= endIndex; i++){
            if (i >= startIndex){
                sublist->Append(current->data);
            }

            current = current->next;
        }

        return sublist;
    }

    int GetLength() override{
        return length;
    }

    void Append(T item) override{
        Node* newNode = new Node(item);

        if (length == 0){
            head = tail = newNode;
        }
        else{
            tail->next = newNode;
            tail = newNode;
        }

        length++;
    }

    void Prepend(T item) override{
        Node* newNode = new Node(item, head);

        if (length == 0){
            head = tail = newNode;
        }
        else{
            head = newNode;
        }

        length++;
    }

    void Concat(Sequence<T>* list) override{
        int length = list->GetLength();
        for (int i = 0; i < length; i++){
            Append(list->GetElement(i));
        }
    }

    void Print() {
        Node* current = head;
        cout << "Elements in the list: ";
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void Clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        length = 0;
    }
};