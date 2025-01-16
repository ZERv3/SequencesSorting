#include "../Cache/LRUCache.h"
#include "Person.h"

void testCache(LRUCache<int, int>& cache) {
    int input, index[10];

    std::cout << "Введите 10 чисел для кэширования:\n";

    // Ввод 10 чисел для заполнения кэша
    for (int i = 0; i < 10; ++i) {
        std::cout << "Введите значение для кэша [" << i << "]: ";
        std::cin >> input;
        cache.Add(i, input);
        std::cout << "Состояние кэша после установки (" << i << ", " << input << "):\n";
        cache.printCache();  // Вывод текущего состояния кэша после добавления
    }

    // Ввод ключей для извлечения значений из кэша
    std::cout << "Введите 10 чисел для получения из кэша:\n";
    for (int i = 0; i < 10; ++i) {
        std::cout << "Введите ключ для получения: ";
        std::cin >> input;
        index[i] = cache.GetValue(input);
        std::cout << "После получения (" << input << "): Значение = " << index[i] << "\n";
        std::cout << "Состояние кэша после получения (" << input << "):\n";
        cache.printCache();  // Вывод текущего состояния кэша после извлечения
    }

    std::cout << "\nТестирование содержимого кэша...\n";

    // Проверка правильности содержимого кэша
    bool testPassed = true;
    for (int i = 0, j = 9; i < 10; ++i, --j) {
        std::cout << "Проверка cache.printList(" << i << "): ";
        std::cout << "Ожидание: " << index[j] << ", Результат: " << cache.GetListValue(i) << "\n";
        if (cache.GetListValue(i) != index[j]) {
            testPassed = false;
            break;
        }
    }

    if (!testPassed) {
        std::cout << "Первый тест провален!\n";
    }
    else {
        std::cout << "Первый тест пройден!\n";
    }

    // Заполнение кэша новыми значениями для второго теста
    std::cout << "\nЗаполнение кэша новыми значениями (от 0 до 9) для второго теста:\n";
    for (int i = 0; i < 10; ++i) {
        cache.Add(i, i);
        std::cout << "После установки(" << i << ", " << i << "):\n";
        cache.printCache();  // Вывод текущего состояния кэша после добавления
    }

    // Ввод ключей для второго теста извлечения значений из кэша
    std::cout << "\nВведите ключи для получения из кэша во втором тесте:\n";
    for (int i = 0; i < 10; ++i) {
        index[i] = cache.GetValue(i);
        std::cout << "После установки(" << i << "): Значение = " << index[i] << "\n";
        std::cout << "Состояние кэша после установки (" << i << "):\n";
        cache.printCache();  // Вывод текущего состояния кэша после извлечения
    }

    testPassed = true;
    for (int i = 0, j = 9; i < 10; ++i, --j) {
        std::cout << "Проверка cache.printList(" << i << "): ";
        std::cout << "Ожидание: " << index[j] << ", Результат: " << cache.GetListValue(i) << "\n";
        if (cache.GetListValue(i) != index[j]) {
            testPassed = false;
            break;
        }
    }

    if (!testPassed) {
        std::cout << "Второй тест провален!\n";
    }
    else {
        std::cout << "Второй тест пройден!\n";
    }
}

void runCacheTest() {
    // Создание экземпляра LRU-кэша
    LRUCache<int, int>* lruCache = new LRUCache<int, int>(10, 10);

    // Тестирование работы кэша
    testCache(*lruCache);

    delete lruCache; // Освобождение памяти
}
