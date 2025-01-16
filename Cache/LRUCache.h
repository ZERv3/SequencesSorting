#pragma once

#include <iostream>
#include "../Hash/IDictionary.h"
// Убираем, т.к. итератор больше не используется
//#include "../Sequences/Iterator.h"

// Структура для представления узла двусвязного списка, содержащего ключ и значение.
template <class TKey, class TValue>
struct NodeList {
    TKey key;         // Ключ узла
    TValue value;     // Значение узла
    NodeList* prev;   // Указатель на предыдущий узел
    NodeList* next;   // Указатель на следующий узел

    // Оператор присваивания для узла списка
    void operator=(NodeList<TKey, TValue>* node) {
        key   = node->key;
        value = node->value;
        next  = node->next;
        prev  = node->prev;
    }

    // Конструктор с инициализацией ключа и значения
    NodeList(TKey key, TValue value)
        : key(key), value(value), prev(nullptr), next(nullptr) {}

    // Конструктор по умолчанию
    NodeList() : prev(nullptr), next(nullptr) {}
};

// Класс реализации LRU-кэша.
template <class TKey, class TValue>
class LRUCache {
private:
    NodeList<TKey, TValue>* head; // Указатель на голову списка
    NodeList<TKey, TValue>* tail; // Указатель на хвост списка
    int size;                     // Максимальный размер кэша
    IDictionary<TKey, NodeList<TKey, TValue>*> id; // Хеш-таблица для быстрого доступа к узлам

public:
    // Конструктор для создания кэша с заданной ёмкостью
    // capacity  - это максимальное количество элементов кэша
    // capacity1 - передаём во внутренний IDictionary (например, чтобы задать ёмкость хеш-таблицы)
    LRUCache(int capacity, int capacity1)
        : head(nullptr),
          tail(nullptr),
          size(capacity),
          id(IDictionary<TKey, NodeList<TKey, TValue>*>(capacity1))
    {
    }

    // Деструктор для освобождения памяти
    ~LRUCache() {
        // Освобождаем все узлы списка
        NodeList<TKey, TValue>* current = head;
        while (current) {
            NodeList<TKey, TValue>* temp = current;
            current = current->next;
            delete temp;
        }
    }

    // Функция для получения значения по *индексу* в списке (НЕ по ключу).
    // Индекс здесь означает, что 0 соответствует head, 1 — следующий узел и т.д.
    // В реальном LRU этот метод не так важен, но если он вам нужен — оставим.
    TValue Get(TKey index) {
        NodeList<TKey, TValue>* node = head;
        for (int i = 0; i < index && node != nullptr; ++i) {
            node = node->next;
        }
        return (node != nullptr) ? node->value : TValue{};
    }

    // Аналогичная функция для получения значения узла на основе индекса
    TValue GetListValue(TKey index) {
        NodeList<TKey, TValue>* node = head;
        for (int i = 0; i < index && node != nullptr; ++i) {
            node = node->next;
        }
        return (node != nullptr) ? node->value : TValue{};
    }
    
    // Проверить, содержится ли ключ в LRUCache
        bool Contains(TKey key) {
            // Если в хеше вернулся nullptr — значит, элемента нет
            NodeList<TKey, TValue>* node = id.GetValue(key);
            return (node != nullptr);
        }

        // Удалить элемент по ключу
        void RemoveKey(TKey key) {
            NodeList<TKey, TValue>* node = id.GetValue(key);
            if (node) {
                // Убираем из двусвязного списка
                Remove(node);
                // Убираем из хеш-таблицы
                id.Remove(key);
            }
        }

    // Добавление/обновление элемента в кэш
    void Add(TKey key, TValue value) {
        // Пытаемся найти узел в хеш-таблице
        NodeList<TKey, TValue>* node = id.GetValue(key);

        // Если элемент уже существует, просто обновляем значение и двигаем его в голову списка
        if (node != nullptr) {
            node->value = value;
            Remove(node);
            SetHead(node);
        }
        else {
            // Создаём новый узел
            NodeList<TKey, TValue>* newNode = new NodeList<TKey, TValue>(key, value);

            // Если в кэше уже максимально допустимое число элементов
            // убираем "хвост" (наименее используемый элемент)
            if (id.GetFullness() >= size) {
                // Сначала удаляем элемент из хеш-таблицы
                id.Remove(tail->key);
                // Затем удаляем его из списка
                Remove(tail);
            }
            // Добавляем в голову
            SetHead(newNode);
            // И записываем в хеш-таблицу
            id.Add(key, newNode);
        }
    }

    // Получение значения элемента по ключу
    // При обращении к элементу в LRU он становится "самым новым" (переводим в head).
    TValue GetValue(TKey key) {
        NodeList<TKey, TValue>* node = id.GetValue(key);
        if (node == nullptr) {
            // Элемент не найден
            return TValue{};
        }
        // Перемещаем в начало списка (как самый недавно использованный)
        Remove(node);
        SetHead(node);
        // Возвращаем значение
        return node->value;
    }

    // Удаление узла из двусвязного списка
    void Remove(NodeList<TKey, TValue>* node) {
        if (node == nullptr) return;

        if (node->prev != nullptr) {
            node->prev->next = node->next;
        } else {
            // Если удаляем голову
            head = node->next;
        }
        if (node->next != nullptr) {
            node->next->prev = node->prev;
        } else {
            // Если удаляем хвост
            tail = node->prev;
        }
        node->prev = nullptr;
        node->next = nullptr;
    }

    // Установка нового узла в начало списка
    void SetHead(NodeList<TKey, TValue>* node) {
        // Новая голова ссылается на старую голову
        node->next = head;
        node->prev = nullptr;

        if (head != nullptr) {
            head->prev = node;
        }
        head = node;

        // Если список был пустым, то head == tail
        if (tail == nullptr) {
            tail = head;
        }
    }

    // Вывод состояния кэша в консоль (для отладки)
    void printCache() {
        NodeList<TKey, TValue>* node = head;
        if (node == nullptr) {
            std::cout << "Кэш пуст." << std::endl;
            return;
        }

        std::cout << "Состояние LRU-кэша (начиная с head):" << std::endl;
        while (node != nullptr) {
            std::cout << "  [Key: " << node->key << ", Value: " << node->value << "]" << std::endl;
            node = node->next;
        }
    }
};
