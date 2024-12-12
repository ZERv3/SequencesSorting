#include <iostream>
#include <fstream>
#include <string>
#include <limits>

// Подключаем заголовочные файлы с тестами
#include "../Tests/SequenceFunctionalTests.h"
#include "../Tests/SequenceStressTests.h"
#include "../Tests/SorterFunctionalTests.h"
#include "../Tests/SorterStressTests.h"
#include "PersonSortingInterface.h"  // Подключаем интерфейс для сортировки Person
#include "IntegerSortingInterface.h" // Интерфейс для сортировки сгенерированных чисел

// Остальной ваш код...

bool SafeReadInt(int &value, bool allowZero = false) {
    std::cin >> value;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    if (!allowZero && value <= 0) {
        return false;
    }
    return true;
}

bool GetStressTestParams(int &minCount, int &maxCount, int &step) {
    std::cout << "Введите минимальное количество объектов (целое число > 0): ";
    if (!SafeReadInt(minCount)) {
        std::cout << "Некорректный ввод. Попробуйте еще раз." << std::endl;
        return false;
    }

    std::cout << "Введите максимальное количество объектов (целое число >= минимального): ";
    if (!SafeReadInt(maxCount)) {
        std::cout << "Некорректный ввод. Попробуйте еще раз." << std::endl;
        return false;
    }

    if (maxCount < minCount) {
        std::cout << "Максимальное количество не может быть меньше минимального." << std::endl;
        return false;
    }

    std::cout << "Введите шаг увеличения числа объектов (целое число > 0): ";
    if (!SafeReadInt(step)) {
        std::cout << "Некорректный ввод. Попробуйте еще раз." << std::endl;
        return false;
    }

    if (step <= 0) {
        std::cout << "Шаг должен быть положительным." << std::endl;
        return false;
    }

    return true;
}

void RunUserInterface() {
    while (true) {
        std::cout << "================ Главное меню ================" << std::endl;
        std::cout << "1) Функциональные тесты последовательностей" << std::endl;
        std::cout << "2) Нагрузочные тесты последовательностей" << std::endl;
        std::cout << "3) Функциональные тесты сортировок" << std::endl;
        std::cout << "4) Нагрузочные тесты сортировок" << std::endl;
        std::cout << "5) Сортировка Person" << std::endl;
        std::cout << "6) Сортировка чисел" << std::endl;
        std::cout << "0) Выход из программы" << std::endl;
        std::cout << "==============================================" << std::endl;
        std::cout << "Выберите пункт меню: ";

        int choice;
        if (!SafeReadInt(choice, true)) {
            std::cout << "Некорректный ввод. Попробуйте еще раз." << std::endl;
            continue;
        }

        if (choice < 0 || choice > 6) {
            std::cout << "Неверный выбор. Попробуйте еще раз." << std::endl;
            continue;
        }

        if (choice == 0) {
            std::cout << "Выход..." << std::endl;
            break;
        }

        switch (choice) {
            case 1: {
                // Функциональные тесты последовательностей
                RunSequenceFunctionalTests();
                break;
            }
            case 2: {
                // Нагрузочные тесты последовательностей
                int minCount, maxCount, step;
                if (!GetStressTestParams(minCount, maxCount, step)) {
                    break;
                }

                {
                    std::ofstream outFile("../Data/SequenceStressTestsData.csv", std::ios::out);
                    if (!outFile) {
                        std::cerr << "Не удалось открыть файл ../Data/SequenceStressTestsData.csv для записи." << std::endl;
                        break;
                    }

                    outFile << "Кол-во элементов,DynamicArray,LinkedList\n";

                    for (int dataSize = minCount; dataSize <= maxCount; dataSize += step) {
                        double daTime = DynamicArrayStressTest(dataSize);
                        double llTime = LinkedListStressTest(dataSize);
                        outFile << dataSize << "," << daTime << "," << llTime << "\n";
                    }
                }

                break;
            }
            case 3: {
                // Функциональные тесты сортировок
                RunSorterFunctionalTests();
                break;
            }
            case 4: {
                // Нагрузочные тесты сортировок
                int minCount, maxCount, step;
                if (!GetStressTestParams(minCount, maxCount, step)) {
                    break;
                }

                {
                    std::ofstream outFile("../Data/SortingStressTestsData.csv", std::ios::out);
                    if (!outFile) {
                        std::cerr << "Не удалось открыть файл ../Data/SortingStressTestsData.csv для записи." << std::endl;
                        break;
                    }

                    outFile << "Кол-во элементов,Insertion Sort,Merge Sort,Quick Sort,Bubble Sort,Pancake Sort\n";

                    for (int dataSize = minCount; dataSize <= maxCount; dataSize += step) {
                        double insertionTime = RunInsertionSortPerformanceTest(dataSize);
                        double mergeTime = RunMergeSortPerformanceTest(dataSize);
                        double quickTime = RunQuickSortPerformanceTest(dataSize);
                        double bubbleTime = RunBubbleSortPerformanceTest(dataSize);
                        double pancakeTime = RunPancakeSortPerformanceTest(dataSize);

                        outFile << dataSize << ","
                                << insertionTime << ","
                                << mergeTime << ","
                                << quickTime << ","
                                << bubbleTime << ","
                                << pancakeTime << "\n";
                    }
                }

                break;
            }
            case 5: {
                // Новый пункт — Сортировка Person
                RunPersonSortingInterface();
                break;
            }

            case 6: {
                RunIntegerSortingMenu();
                break;
            }
        }
    }
}