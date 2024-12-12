#include <iostream>
#include <fstream>
#include "../Sequences/DynamicArray.h"
#include "../Sorting/SortingAlgorithms.h"
#include "../Generators/IntegerDataGenerator.h"

inline bool AscendingInt(const int &a, const int &b) {
    return a < b;
}

inline bool DescendingInt(const int &a, const int &b) {
    return a > b;
}

bool LoadIntegersFromFile(const std::string& filename, Sequence<int>& sequence) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Не удалось открыть файл " << filename << " для чтения." << std::endl;
        return false;
    }

    sequence.Clear();

    int value;
    while (inFile >> value) {
        sequence.PushFront(value);
    }

    return true;
}

bool SaveIntegersToFile(const std::string& filename, Sequence<int>& sequence) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Не удалось открыть файл " << filename << " для записи." << std::endl;
        return false;
    }

    for (int i = 0; i < sequence.GetLength(); i++) {
        outFile << sequence.GetElement(i) << "\n";
    }

    return true;
}

void RunIntegerSortingMenu() {
    while (true) {
        std::cout << "========== Меню сортировки чисел ==========" << std::endl;
        std::cout << "1) Генерация чисел" << std::endl;
        std::cout << "2) Сортировка чисел" << std::endl;
        std::cout << "0) Вернуться в главное меню" << std::endl;

        int choice;
        std::cin >> choice;
        if (std::cin.fail() || choice < 0 || choice > 2) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод, попробуйте еще раз." << std::endl;
            continue;
        }

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1: {
                // Генерация чисел
                int minVal, maxVal, count;
                std::cout << "Введите минимальное значение: ";
                std::cin >> minVal;
                std::cout << "Введите максимальное значение: ";
                std::cin >> maxVal;
                std::cout << "Введите количество чисел: ";
                std::cin >> count;

                if (GenerateIntegersToFile(minVal, maxVal, count, "../Data/IntegersDataPregenerated.txt")) {
                    std::cout << "Данные сгенерированы в ../Data/IntegersDataPregenerated.txt" << std::endl;
                } else {
                    std::cout << "Произошла ошибка при генерации данных." << std::endl;
                }
                break;
            }
            case 2: {
                // Сортировка чисел
                // Загружаем данные
                DynamicArray<int> intSequence;
                if (!LoadIntegersFromFile("../Data/IntegersDataPregenerated.txt", intSequence)) {
                    std::cout << "Не удалось загрузить данные из ../Data/IntegersDataPregenerated.txt" << std::endl;
                    break;
                }

                // Выбор алгоритма сортировки
                while (true) {
                    std::cout << "Выберите алгоритм сортировки:" << std::endl;
                    std::cout << "1) Сортировка вставкой (InsertionSort)" << std::endl;
                    std::cout << "2) Сортировка слиянием (MergeSort)" << std::endl;
                    std::cout << "3) Быстрая сортировка (QuickSort)" << std::endl;
                    std::cout << "4) Пузырьковая сортировка (BubbleSort)" << std::endl;
                    std::cout << "5) Блинная сортировка (PancakeSort)" << std::endl;
                    std::cout << "0) Вернуться" << std::endl;

                    int algChoice;
                    std::cin >> algChoice;
                    if (std::cin.fail() || algChoice < 0 || algChoice > 5) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Некорректный ввод, попробуйте еще раз." << std::endl;
                        continue;
                    }

                    if (algChoice == 0) {
                        break;
                    }

                    // Выбор порядка сортировки
                    while (true) {
                        std::cout << "Выберите порядок сортировки:" << std::endl;
                        std::cout << "1) По возрастанию" << std::endl;
                        std::cout << "2) По убыванию" << std::endl;
                        std::cout << "0) Вернуться" << std::endl;

                        int orderChoice;
                        std::cin >> orderChoice;
                        if (std::cin.fail() || orderChoice < 0 || orderChoice > 2) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Некорректный ввод, попробуйте еще раз." << std::endl;
                            continue;
                        }

                        if (orderChoice == 0) {
                            break;
                        }

                        bool (*comparator)(const int&, const int&) = (orderChoice == 1) ? AscendingInt : DescendingInt;

                        ISorter<int>* sorter = nullptr;
                        switch (algChoice) {
                            case 1: sorter = new InsertionSorter<int>(); break;
                            case 2: sorter = new MergeSorter<int>(); break;
                            case 3: sorter = new QuickSorter<int>(); break;
                            case 4: sorter = new BubbleSorter<int>(); break;
                            case 5: sorter = new PancakeSorter<int>(); break;
                        }

                        if (sorter && comparator) {
                            sorter->Sort(intSequence, comparator);
                            delete sorter;
                            sorter = nullptr;

                            if (SaveIntegersToFile("../Data/IntegersDataPregeneratedSORTED.txt", intSequence)) {
                                std::cout << "Сортировка выполнена. Результаты в ../Data/IntegersDataPregeneratedSORTED.txt" << std::endl;
                            } else {
                                std::cout << "Не удалось сохранить результаты." << std::endl;
                            }
                        }

                        break; // Выходим из меню порядка сортировки
                    }

                    break; // Выходим из меню выбора алгоритма
                }

                break;
            }
        }
    }
}