#include "DictionaryTests.h"
#include <iostream>
#include <chrono>
#include <random>

// Утилита для удобного замера времени
class Timer {
public:
    Timer() { reset(); }
    void reset() {
        m_start = std::chrono::high_resolution_clock::now();
    }
    double elapsedMilliseconds() const {
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::milli>(end - m_start).count();
    }
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
};

// Функция для среднего времени выполнения операции "Add"
template <typename TDictionary>
double BenchmarkAdd(TDictionary& dict,
                    const std::vector<int>& keys,
                    const std::vector<int>& values)
{
    // Убеждаемся, что длины совпадают
    size_t N = keys.size();
    Timer timer;
    for (size_t i = 0; i < N; i++) {
        dict.Add(keys[i], values[i]);
    }
    double totalMs = timer.elapsedMilliseconds();
    return totalMs / static_cast<double>(N);  // среднее время на одну операцию
}

// Функция для среднего времени выполнения операции "GetValue"
template <typename TDictionary>
double BenchmarkGetValue(TDictionary& dict,
                         const std::vector<int>& keys)
{
    size_t N = keys.size();
    Timer timer;
    for (size_t i = 0; i < N; i++) {
        // Просто читаем, неважно, что дальше делаем
        volatile auto val = dict.GetValue(keys[i]);
        (void)val;
    }
    double totalMs = timer.elapsedMilliseconds();
    return totalMs / static_cast<double>(N);
}

// Функция для среднего времени выполнения операции "Remove"
template <typename TDictionary>
double BenchmarkRemove(TDictionary& dict,
                       const std::vector<int>& keys)
{
    size_t N = keys.size();
    Timer timer;
    for (size_t i = 0; i < N; i++) {
        dict.Remove(keys[i]);
    }
    double totalMs = timer.elapsedMilliseconds();
    return totalMs / static_cast<double>(N);
}

// Вспомогательная функция для вывода результатов и их сравнения
void PrintComparison(const std::string& operationName,
                     double msPerOpDict1,
                     double msPerOpDict2)
{
    std::cout << "\n--- " << operationName << " ---\n";
    std::cout << "Dict1 (IDictionary)  : " << msPerOpDict1 << " ms/op\n";
    std::cout << "Dict2 (LRUCacheDict) : " << msPerOpDict2 << " ms/op\n";

    // Считаем, на сколько процентов Dict2 быстрее/медленнее
    // Отталкиваемся от времени Dict1 как базового
    double diff = (msPerOpDict2 - msPerOpDict1) / msPerOpDict1 * 100.0;
    if (diff < 0) {
        std::cout << "LRUCacheDictionary быстрее примерно на "
                  << -diff << "%\n";
    } else {
        std::cout << "LRUCacheDictionary медленнее примерно на "
                  << diff << "%\n";
    }
}

void RunDictionaryTests(int capacity, int cacheSize){
    // 1) Создаём два словаря:
    // Обычный на основе HashTable
    IDictionary<int, int> dict1(capacity);  // capacity для HashTable (примерное)
    
    // LRUCacheDictionary, где LRUCache имеет capacity=100,
    // а внутренний HashTable, допустим, 200.
    LRUCacheDictionary<int, int> dict2(cacheSize, capacity);

    // 2) Генерируем тестовые данные
    const size_t N = 10000;  // число элементов
    std::vector<int> keys(N), vals(N);
    
    // Для случайных чисел:
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distKey(0, 200000);
    std::uniform_int_distribution<int> distVal(0, 1000000);

    for (size_t i = 0; i < N; i++) {
        keys[i] = distKey(gen);
        vals[i] = distVal(gen);
    }

    // 3) Тестируем скорость ADD (добавление)
    double addTimeDict1 = BenchmarkAdd(dict1, keys, vals);
    double addTimeDict2 = BenchmarkAdd(dict2, keys, vals);

    // 4) Тестируем скорость GET (чтение)
    double getTimeDict1 = BenchmarkGetValue(dict1, keys);
    double getTimeDict2 = BenchmarkGetValue(dict2, keys);

    // 5) Тестируем скорость REMOVE
    double removeTimeDict1 = BenchmarkRemove(dict1, keys);
    double removeTimeDict2 = BenchmarkRemove(dict2, keys);

    // 6) Выводим результаты
    PrintComparison("Add (вставка)", addTimeDict1, addTimeDict2);
    PrintComparison("GetValue (чтение)", getTimeDict1, getTimeDict2);
    PrintComparison("Remove (удаление)", removeTimeDict1, removeTimeDict2);
}
