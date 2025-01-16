#pragma once

#include "../Sequences/LinkedList.h"
#include "Functional.h"

template <typename TKey, typename TValue>
class HashTable;

//Шаблонный класс элемента хеш-таблицы
template <typename TKey, typename TValue>
class HT_Item {
    friend class HashTable<TKey, TValue>;
private:
    TKey key;
    TValue value;
public:
    //Конструктор элемента
    HT_Item(): key(TKey()), value(TValue()){};
    
    HT_Item(TKey key, TValue value): key(key), value(value){};
    
    //Получить ключ
    TKey GetKey() const {return this->key;}
    
    //Получить значение
    TValue GetValue() const {return this->value;}
    
    TValue& GetElement() {return this->value;}
    
    //Установить значение
    void SetValue(TValue value){this->value = value;}
    
    //Получить указатель на значение
    TValue* GetValuePointer(){return &this->value;}
    
    //Проверка на заполняемость
    bool IsEmpty(){return (this->value == TValue());}
    
    bool operator==(const HT_Item<TKey, TValue>& other){
        return (chf::isEqual(this->key, other.GetKey()) && chf::isEqual(this->value, other.GetValue()));
    }
    
    friend std::ostream& operator<<(std::ostream& outStream, const HT_Item<TKey, TValue>& item) {
        outStream << "[" << item.key << " , " << item.value << "]";
        return outStream;
    }
};

//Шаблонный класс хеш-таблицы
template <typename TKey, typename TValue>
class HashTable{
private:
    LinkedList<HT_Item<TKey, TValue>> items; //Пока затруднена реализация упрощения
    LinkedList<HT_Item<TKey, TValue>*>* data; //Элементы - указатели на объекты
    unsigned int capacity; //Емкость
    unsigned int fullness; //Заполненность
public:
    //Основной конструктор
    HashTable(unsigned int capacity):
        capacity(capacity),
        fullness(0),
        data(new LinkedList<HT_Item<TKey, TValue>*>[capacity]),
        items(LinkedList<HT_Item<TKey, TValue>>()){}
    
    int GetCapacity() const {
        return this->capacity;
    }
    
    int GetFullness() const {
        return this->fullness;
    }
    
    LinkedList<HT_Item<TKey, TValue>*>* GetData() const {
        return this->data;
    }
    
    LinkedList<HT_Item<TKey, TValue>> GetItems() const {
        return this->items;
    }
    
    //Добавление элемента в список
    HT_Item<TKey, TValue>* ItemsAdd(TKey key, TValue value){
        HT_Item<TKey, TValue> item(key, value);
        
        auto current = this->items.GetNode(0);
        if(current != nullptr){
            int i = 0;
            while(current != nullptr){
                auto curKey = current->data.GetKey();
                if(chf::isEqual(curKey, key)){
                    current->data.SetValue(value);
                    return &(items.GetElement(i));
                }
                else{
                    current = current->next;
                    i++;
                }
            }
        }
        
        this->items.PushFront(item);
        return &(items.GetTail());
    }
    
    //Поисковик локального индекса (Рабочий)
    int FindKeyListIndex(TKey key){
        int hKey = chf::hash(key, this->GetCapacity());
        
        auto current = this->data[hKey].GetNode(0);
        
        if(current != nullptr){
            int i = 0;
            while(current != nullptr){
                auto curKey = current->data->GetKey();
                if(chf::isEqual(curKey, key)){
                    return i;
                }
                else{
                    i++;
                    current = current->next;
                }
            }
        }
        return -1;
    }
    
    bool Contains(TKey key){
        return (FindKeyListIndex(key)!=-1);
    }
    
    TValue GetValue(TKey key) {
        int index = FindKeyListIndex(key);
        if(index==-1){
            return TValue();
        }
        auto hKey = chf::hash(key, this->capacity);
        return (this->data[hKey].GetElement(index)->GetValue());
    }
    
    TValue& GetElement(TKey key) {
        int index = FindKeyListIndex(key);
        auto hKey = chf::hash(key, this->capacity);
        return (this->data[hKey].GetElement(index)->GetElement());
    }
    
    void Insert(TKey key, TValue value) {
        auto item = ItemsAdd(key, value);
        InsertInternal(item);
    }

    void Insert(HT_Item<TKey, TValue>* item) {
        InsertInternal(item);
    }

    // Внутренний метод для добавления элемента
    void InsertInternal(HT_Item<TKey, TValue>* item) {
        auto key = item->GetKey();
        int hKey = chf::hash(key, this->GetCapacity()); // Хэш-ключ (Индекс списка)
        auto& list = this->data[hKey]; // Ссылка на список по индексу
        bool itemEdited = false;

        auto current = list.GetNode(0);
        while (current != nullptr) {
            auto curKey = current->data->GetKey();
            if (chf::isEqual(curKey, key)) {
                itemEdited = true; // Найден элемент с таким же ключом
                break;
            }
            current = current->next;
        }

        if (!itemEdited) {
            list.PushFront(item);
            this->fullness++;
        }
    }
    
    void Refill(){
        this->fullness = 0;
        int len = this->items.GetLength();
        if(len == 0) {}
        if(len == 1){
            auto current = this->items.GetElement(0);
            Insert(&current);
        }
        if(len > 1){
            auto current = this->items.GetNode(0);
            while(current != nullptr){
                Insert(&(current->data));
                current = current->next;
            }
        }
        
    }
    
    void AutoResize(double limitLoadFactor, int multiplier) {
        double loadFactor = static_cast<double>(GetFullness()) / static_cast<double>(GetCapacity());
        if(loadFactor > limitLoadFactor) {
//            std::cout << "Load Factor: " << loadFactor << "\n";
            
            //Удаляем старую хэш-таблицу
            delete[] this->data;
            
            //Расширенная пустая хэш-таблица
            this->data = new LinkedList<HT_Item<TKey, TValue>*>[capacity*multiplier];
            this->capacity*=multiplier;
            Refill();
        }
    }
    
    void Add(TKey key, TValue value){
        AutoResize(0.75, 2);
        Insert(key, value);
    }
    
    bool Remove(TKey key, TValue value) {
        int hKey = chf::hash(key, this->GetCapacity());
        auto toDelete = new HT_Item<TKey, TValue>(key,value);
        int index = (this->data[hKey]).GetLength() > 0 ? FindKeyListIndex(key) : -1;
        int itemsIndex = (this->items).GetLength() > 0 ? this->items.FindIndex(*toDelete) : -1;
        
        if (index != -1) {
            this->data[hKey].Remove(index);
            this->items.Remove(itemsIndex);
            this->fullness--;
            return true;
        }
        else{return false;}
    }
    
    int FindKeyItemsIndex(TKey key){
        auto current = this->items.GetNode(0);
        
        if(current != nullptr){
            int i = 0;
            while(current != nullptr){
                auto curKey = current->data.GetKey();
                if(chf::isEqual(curKey, key)){
                    return i;
                }
                else{
                    i++;
                    current = current->next;
                }
            }
        }
        return -1;
    }
    
    bool Remove(TKey key) {
        int hKey = chf::hash(key, this->GetCapacity());
        int index = (this->data[hKey]).GetLength() > 0 ? FindKeyListIndex(key) : -1;
        int itemsIndex = (this->items).GetLength() > 0 ? FindKeyItemsIndex(key) : -1;
        
        if (index != -1) {
            this->data[hKey].Remove(index);
            this->items.Remove(itemsIndex);
            this->fullness--;
            return true;
        }
        else{return false;}
    }
    
    friend std::ostream& operator<<(std::ostream& outStream, const HashTable<TKey, TValue>& HT) {
        outStream << "HASHTABLE:" << std::endl;
        auto HTData = HT.GetData();
        for (int i = 0; i < HT.GetCapacity(); i++) {
            auto list = HTData[i];
            outStream << "\t" << HTData[i] << std::endl;
        }
        return outStream;
    }
};

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//        if(len == 0){
//            this->items.PushFront(item);
//            return &(items.GetElement(0));
//        }
//        if(len == 1){
//            auto current = this->items.GetNode(0);
//            auto curKey = current->data.GetKey();
//            if(chf::isEqual(curKey, key)){
//                current->data.SetValue(value);
//                return &(items.GetElement(0));
//            }
//            else{
//                this->items.PushFront(item);
//                return &(items.GetElement(1));
//            }
//        }
//        else{
//            //Получаем хэш-ключ
//            int hKey = chf::hash(key, this->capacity);
//
//            //Булы для условий
//            bool keyUsed = false; //Ключ был ранее использован
//            bool itemAdded = false; //Объект был установлен
//
//            //Ищем последовательность с тем же хэш-ключом
//            auto current = this->items.GetNode(0);
//            for (int i = 0; i < len; i++) {
////                std::cout << current->data;
//                auto curKey = current->data.GetKey();
//                //Если мы нашли брата по хэш-ключу
//                if(chf::hash(curKey, this->capacity) == hKey){
//                    if(!keyUsed){keyUsed = true;}
//                    //Проверяем, не такой же ли полный ключ
//                    if(chf::isEqual(curKey, key)){
//                        current->data.SetValue(value);
//                        return &(items.GetElement(i));
//                    }
//                    //
//                    else{
//                        current = current->next;
//                        continue;
//                    }
//
//
//                }
//                else{
//                    //Если мы нашли брата и встретили другого
//                    if(keyUsed){
//                        this->items.Insert(item, i);
//                        itemAdded = true;
//                        return &(items.GetElement(i));
//                    }
//                    //Ищем брата
//                    else{
//                        current = current->next;
//                    }
//                }
//            }
//            //Не нашли брата
//            if(itemAdded == false){
//                this->items.PushFront(item);
//                return &(items.GetElement(len));
//            }
//        }
//        //Заглушка
//        return nullptr;
//    }

//=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//        int len = this->data[hKey].GetLength();
//        if(len == 0){
////            std::cout << "LEN = " << len;
//            return -1;
//        }
//        if(len == 1){
////            std::cout << "LEN = " << len;
//            auto current = this->data[hKey].GetNode(0);
//
//            auto curKey = current->data->GetKey();
//            if(chf::isEqual(curKey, key)){
//                return 0;
//            }
//            else{
//                return -1;
//            }
//        }
//        if(len > 1){
////            std::cout << "LEN = " << len;
//            auto current = this->data[hKey].GetNode(0);
//            int i = 0;
//            while(current != nullptr){
//                auto curKey = current->data->GetKey();
//                if(chf::isEqual(curKey, key)){
//                    return i;
//                }
//                else{
//                    i++;
//                    current = current->next;
//                }
//            }
//            return -1;
//        }
//        return -1;
//    }
        
//    void Insert(TKey key, TValue value){
//        auto item = ItemsAdd(key, value);
//
//        int hKey = chf::hash(key, this->GetCapacity()); // хэш-ключ (Индекс списка)
//
//        auto list = this->data[hKey];
//
//        int len = list.GetLength();
//        bool itemEdited = false;
//        if(len > 1){
//            auto current = list.GetNode(0);
//            while(current != nullptr){
//                auto curKey = current->data->GetKey();
//                if(chf::isEqual(curKey, key)){
//                    itemEdited = true;
//                    break;
//                }
//                else{
//                    current = current->next;
//                }
//            }
//            if(itemEdited == false){
//                this->data[hKey].PushFront(item);
//                this->fullness++;
//            }
//        }
//        if(len == 1){
//            auto current = list.GetNode(0);
//            auto curKey = current->data->GetKey();
//
//            if(!chf::isEqual(curKey, key)){
//                this->data[hKey].PushFront(item);
//                this->fullness++;
//            }
//        }
//        if(len == 0){
//            this->data[hKey].PushFront(item);
//            this->fullness++;
//        }
//    }
//
//    void Insert(HT_Item<TKey, TValue>* item){
//        auto key = item->GetKey();
//
//        int hKey = chf::hash(key, this->GetCapacity()); // хэш-ключ (Индекс списка)
//
//        auto list = this->data[hKey];
//
//        int len = list.GetLength();
//        bool itemEdited = false;
//
//        if(len > 1){
//            auto current = list.GetNode(0);
//            while(current != nullptr){
//                auto curKey = current->data->GetKey();
//                if(chf::isEqual(curKey, key)){
//                    itemEdited = true;
//                    break;
//                }
//                else{
//                    current = current->next;
//                }
//            }
//            if(itemEdited == false){
//                this->data[hKey].PushFront(item);
//                this->fullness++;
//            }
//        }
//        if(len == 1){
//            auto current = list.GetNode(0);
//            auto curKey = current->data->GetKey();
//
//            if(!chf::isEqual(curKey, key)){
//                this->data[hKey].PushFront(item);
//                this->fullness++;
//            }
//        }
//        if(len == 0){
//            this->data[hKey].PushFront(item);
//            this->fullness++;
//        }
//    }
