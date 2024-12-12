#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "../Sequences/DynamicArray.h"
#include "../Sequences/LinkedList.h"
#include "../Sorting/SortingAlgorithms.h"
#include "../Tests/Person.h"
#include "../Tests/Extractor.h"

// Компараторы для Extractor<Person> (по разным полям и направлениям)
bool CompareExtractorFirstNameAsc(const Extractor<Person>& a, const Extractor<Person>& b) {
    return a.value.firstName < b.value.firstName;
}
bool CompareExtractorFirstNameDesc(const Extractor<Person>& a, const Extractor<Person>& b) {
    return a.value.firstName > b.value.firstName;
}

bool CompareExtractorLastNameAsc(const Extractor<Person>& a, const Extractor<Person>& b) {
    return a.value.lastName < b.value.lastName;
}
bool CompareExtractorLastNameDesc(const Extractor<Person>& a, const Extractor<Person>& b) {
    return a.value.lastName > b.value.lastName;
}

bool CompareExtractorIdAsc(const Extractor<Person>& a, const Extractor<Person>& b) {
    return a.value.id < b.value.id;
}
bool CompareExtractorIdDesc(const Extractor<Person>& a, const Extractor<Person>& b) {
    return a.value.id > b.value.id;
}

bool CompareExtractorBirthYearAsc(const Extractor<Person>& a, const Extractor<Person>& b) {
    return a.value.birthYear < b.value.birthYear;
}
bool CompareExtractorBirthYearDesc(const Extractor<Person>& a, const Extractor<Person>& b) {
    return a.value.birthYear > b.value.birthYear;
}

bool CompareExtractorHeightAsc(const Extractor<Person>& a, const Extractor<Person>& b) {
    return a.value.height < b.value.height;
}
bool CompareExtractorHeightDesc(const Extractor<Person>& a, const Extractor<Person>& b) {
    return a.value.height > b.value.height;
}

bool CompareExtractorWeightAsc(const Extractor<Person>& a, const Extractor<Person>& b) {
    return a.value.weight < b.value.weight;
}
bool CompareExtractorWeightDesc(const Extractor<Person>& a, const Extractor<Person>& b) {
    return a.value.weight > b.value.weight;
}

// Функция загрузки Person из файла.
bool LoadPersonsFromFile(const std::string& filename, Sequence<Extractor<Person>>& sequence) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Не удалось открыть файл " << filename << " для чтения." << std::endl;
        return false;
    }

    sequence.Clear();
    Person p;
    int i = 0;
    while (inFile >> p) {
        Extractor<Person> ex(i++, p);
        sequence.PushFront(ex);
    }

    return true;
}

// Сохранение отсортированных данных в CSV
bool SavePersonsToCSV(const std::string& filename, Sequence<Extractor<Person>>& sequence) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Не удалось открыть файл " << filename << " для записи." << std::endl;
        return false;
    }

    // Заголовок CSV
    outFile << "id,firstName,lastName,birthYear,height,weight\n";
    for (int i = 0; i < sequence.GetLength(); i++) {
        const Extractor<Person>& ex = sequence.GetElement(i);
        const Person& p = ex.value;
        outFile << p.id << ","
                << p.firstName << ","
                << p.lastName << ","
                << p.birthYear << ","
                << p.height << ","
                << p.weight << "\n";
    }

    return true;
}

// Функция сортировки Person через Extractor
void RunPersonSortingInterface() {
    while (true) {
        std::cout << "=========== Меню сортировки Person ===========" << std::endl;
        std::cout << "Выберите сортировку:" << std::endl;
        std::cout << "1) Сортировка вставкой" << std::endl;
        std::cout << "2) Сортировка слиянием" << std::endl;
        std::cout << "3) Быстрая сортировка (Quick Sort)" << std::endl;
        std::cout << "4) Пузырьковая сортировка (Bubble Sort)" << std::endl;
        std::cout << "5) Блинная сортировка (Pancake Sort)" << std::endl;
        std::cout << "0) Вернуться в главное меню" << std::endl;

        int sortChoice;
        std::cin >> sortChoice;
        if (std::cin.fail() || sortChoice < 0 || sortChoice > 5) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод, попробуйте еще раз." << std::endl;
            continue;
        }

        if (sortChoice == 0) {
            break;
        }

        while (true) {
            std::cout << "Выберите поле для сортировки Person:" << std::endl;
            std::cout << "1) firstName" << std::endl;
            std::cout << "2) lastName" << std::endl;
            std::cout << "3) id" << std::endl;
            std::cout << "4) birthYear" << std::endl;
            std::cout << "5) height" << std::endl;
            std::cout << "6) weight" << std::endl;
            std::cout << "0) Вернуться к выбору сортировки" << std::endl;

            int fieldChoice;
            std::cin >> fieldChoice;
            if (std::cin.fail() || fieldChoice < 0 || fieldChoice > 6) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Некорректный ввод, попробуйте еще раз." << std::endl;
                continue;
            }

            if (fieldChoice == 0) {
                break;
            }

            while (true) {
                std::cout << "Выберите порядок сортировки:" << std::endl;
                std::cout << "1) По возрастанию" << std::endl;
                std::cout << "2) По убыванию" << std::endl;
                std::cout << "0) Вернуться к выбору поля" << std::endl;

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

                bool (*comparator)(const Extractor<Person>&, const Extractor<Person>&) = nullptr;

                // Выбираем компаратор, исходя из fieldChoice и orderChoice
                switch (fieldChoice) {
                    case 1: // firstName
                        comparator = (orderChoice == 1) ? CompareExtractorFirstNameAsc : CompareExtractorFirstNameDesc;
                        break;
                    case 2: // lastName
                        comparator = (orderChoice == 1) ? CompareExtractorLastNameAsc : CompareExtractorLastNameDesc;
                        break;
                    case 3: // id
                        comparator = (orderChoice == 1) ? CompareExtractorIdAsc : CompareExtractorIdDesc;
                        break;
                    case 4: // birthYear
                        comparator = (orderChoice == 1) ? CompareExtractorBirthYearAsc : CompareExtractorBirthYearDesc;
                        break;
                    case 5: // height
                        comparator = (orderChoice == 1) ? CompareExtractorHeightAsc : CompareExtractorHeightDesc;
                        break;
                    case 6: // weight
                        comparator = (orderChoice == 1) ? CompareExtractorWeightAsc : CompareExtractorWeightDesc;
                        break;
                }

                if (!comparator) {
                    std::cout << "Ошибка выбора компаратора." << std::endl;
                    break;
                }

                DynamicArray<Extractor<Person>> personSequence;
                if (!LoadPersonsFromFile("../Data/PersonDataPregenerated.txt", personSequence)) {
                    std::cout << "Не удалось загрузить данные Person." << std::endl;
                    break;
                }

                ISorter<Extractor<Person>>* sorter = nullptr;
                switch (sortChoice) {
                    case 1: sorter = new InsertionSorter<Extractor<Person>>(); break;
                    case 2: sorter = new MergeSorter<Extractor<Person>>(); break;
                    case 3: sorter = new QuickSorter<Extractor<Person>>(); break;
                    case 4: sorter = new BubbleSorter<Extractor<Person>>(); break;
                    case 5: sorter = new PancakeSorter<Extractor<Person>>(); break;
                }

                if (sorter && comparator) {
                    sorter->Sort(personSequence, comparator);
                    delete sorter;
                    sorter = nullptr;

                    if (!SavePersonsToCSV("../Data/PersonDataPregeneratedSORTED.csv", personSequence)) {
                        std::cout << "Не удалось сохранить результаты сортировки." << std::endl;
                    } else {
                        std::cout << "Сортировка выполнена. Результаты сохранены в Data/PersonDataPregeneratedSORTED.csv" << std::endl;
                    }
                }

                break; // после сортировки и сохранения выходим из меню порядка
            }

            // Выход из меню полей
            if (fieldChoice != 0) break;
        }
    }
}