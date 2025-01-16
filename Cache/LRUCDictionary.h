#pragma once
#include <cstdlib>    // для rand(), если нужно
#include "LRUCache.h" //

// Простенький класс-обёртка, который внешне повторяет логику IDictionary,
// но внутри «упаковывает» всё в LRUCache.
template <typename TKey, typename TValue>
class LRUCacheDictionary {
private:
    // Здесь заводим LRUCache на 100 элементов.
    // Вторым параметром задаём размер внутренней HashTable,
    // пусть тоже будет 128 или 200 — на ваш выбор.
    LRUCache<TKey, TValue> cache;

public:
    // Конструктор: создаём LRUCache фиксированной ёмкости 100
    LRUCacheDictionary()
        : cache(100, 200) // 100 — «видимый» размер LRU, 200 — размер внутренней HashTable
    {}
    // Конструктор с параметрами: позволяет задать размеры явно
     LRUCacheDictionary(int capacity, int capacityHidden)
         : cache(capacity, capacityHidden)
     {}
        
    // Добавление элемента
    void Add(TKey key, TValue value) {
        cache.Add(key, value);
    }

    // Удаление по ключу
    void Remove(TKey key) {
        cache.RemoveKey(key);
    }

    // Проверка наличия ключа
    bool Contains(TKey key) {
        return cache.Contains(key);
    }

    // Получение значения по ключу
    TValue GetValue(TKey key) {
        return cache.GetValue(key);
    }

    // Для тестов или отладки — можно добавить метод печати содержимого
    void PrintAll() {
        cache.printCache();
    }

    // Генерация данных (пример, аналогично тому, что у вас в IDictionary::Generate).
    // Если нужно, чтобы ключи были целыми от 0 до 9, а значения — случайные,
    // можем сделать так:
    void Generate(int count = 10) {
        for (TKey i = 0; i < count; ++i) {
            this->Add(i, rand() % 256);
        }
    }
};
