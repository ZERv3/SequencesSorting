#include <fstream>
#include <iostream>
#include <ctime>
#include <memory>

#include "TestsCache.h"

// Вывод всех элементов кэша в консоль.
void printCache(LRUCache<int, int>& cache) {
    std::cout << "Вывод всех элементов кэша:\n";
    for (int i = 0; i < PERSON_COUNT; ++i) {
        std::cout << cache.GetListValue(i) << '\n'; // Вывод значения элемента по индексу.
    }
    std::cout << '\n';
}

// Запись всех элементов кэша в текстовый файл.
void writeToFile(LRUCache<int, int>& cache) {
    std::ofstream fout("TestFile.txt");
    if (!fout) {
        std::cerr << "Ошибка открытия файла записи!" << std::endl; // Обработка ошибки открытия файла.
        return;
    }
    for (int i = 0; i < PERSON_COUNT; ++i) {
        fout << cache.GetValue(1) << '\n'; // Запись значений кэша в файл.
    }
    fout.close(); // Закрытие файла после записи.
}

// Измерение времени выполнения операций вывода содержимого кэша.
void measureTimeForCache(LRUCache<int, int>& cache) {
    clock_t start = clock(); // Фиксация начального времени.
    for (int i = 0; i < PERSON_COUNT; ++i) {
        std::cout << cache.GetListValue(i) << '\n'; // Вывод значений кэша.
    }
    clock_t end = clock(); // Фиксация конечного времени.
    float seconds = static_cast<float>(end - start) / CLOCKS_PER_SEC; // Расчет времени выполнения.
    std::cout << "\nВремя выполнения кэширования: " << seconds << " секунд\n";
}

// Измерение времени выполнения операций вывода данных объектов Person.
void measureTimeForPerson(Person person[]) {
    clock_t start = clock(); // Фиксация начального времени.
    for (int i = 0; i < PERSON_COUNT; ++i) {
        std::cout << person[i].GetBirthYear() << '\n'; // Вывод значения поля weight каждого объекта.
    }
    clock_t end = clock(); // Фиксация конечного времени.
    float seconds = static_cast<float>(end - start) / CLOCKS_PER_SEC; // Расчет времени выполнения.
    std::cout << "\nВремя выполнения Person: " << seconds << " секунд\n";
}

// Управление основными операциями с кэшем и объектами Person.
void runCacheOperations() {
    srand(static_cast<unsigned int>(time(nullptr))); // Инициализация генератора случайных чисел.

    Person person[PERSON_COUNT]; // Массив объектов Person.
    auto lruCache = std::make_unique<LRUCache<int, int>>(CACHE_SIZE, CACHE_SIZE); // Создание экземпляра LRU-кэша.

    // Генерация данных для каждого объекта Person.
    for (int i = 0; i < PERSON_COUNT; ++i) {
        person[i].generation(); // Заполнение объекта случайными данными.
    }

    // Заполнение кэша значениями age из объектов Person.
    for (int i = 0; i < PERSON_COUNT; ++i) {
        lruCache->Add(i, person[i].GetBirthYear()); // Установка ключа и значения в кэш.
    }

    // Вывод содержимого кэша в консоль.
    printCache(*lruCache);

    // Сохранение содержимого кэша в файл.
    writeToFile(*lruCache);

    // Измерение времени операций с кэшем.
    measureTimeForCache(*lruCache);

    // Измерение времени операций с объектами Person.
    measureTimeForPerson(person);
}
