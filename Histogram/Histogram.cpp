#include "Histogram.h"
#include <iostream>
#include <string>
#include <algorithm>

#include "../Sequences/LinkedList.h"
#include "../ObjectClasses/ISortedSequence.h"
#include "../ObjectClasses/ISet.h"

void InterfaceForHistogramPeople() {
    srand(static_cast<unsigned int>(time(nullptr)));

    // Создание списка объектов Person
    LinkedList<Person> persons;

    for (int i = 0; i < 100; ++i) {
        Person p;
        p.generation();
        persons.PushFront(p);
    }

    // Запрос у пользователя: вывести список?
    std::string variant1;
    std::cout << "Вывести список? (Y/N)" << std::endl;
    std::cin >> variant1;

    // Преобразование ввода в верхний регистр для унификации
    std::transform(variant1.begin(), variant1.end(), variant1.begin(), ::toupper);

    if (!variant1.empty()) {
        char firstChar = variant1[0];
        switch (firstChar) {
        case 'Y':
            persons.Print(); // Печать списка
            break;
        case 'N':
            break;
        default:
            std::cout << "Неверный ввод. Выход." << std::endl;
            return;
        }
    } else {
        std::cout << "Неверный ввод. Выход." << std::endl;
        return;
    }

    // Выбор операции: продолжить или нет
    std::cout << "Вывести Гистограму с дубликатами? (Y/N): " << std::endl;
    std::string change;
    std::cin >> change;

    // Лямбда-функции для извлечения свойств объекта Person
    auto getBirthYear = [](const Person& person) -> int { return person.GetBirthYear(); };
    auto getHeight = [](const Person& person) -> int { return person.GetHeight(); };
    auto getWeight = [](const Person& person) -> int { return person.GetWeight(); };

    if (!change.empty()) {
        char option = toupper(change[0]);

        switch (option) {
        case 'Y': {
            // Создание множества для удаления дубликатов
            ISet<Person> mySet(persons);
            int variant = 0;
            std::cout << "Выберите гистограмму: 1 - Возраст, 2 - Рост, 3 - Вес\n";
            std::cin >> variant;

            switch (variant) {
            case 1:
                    PrintHistogram<Person, int>(mySet, getBirthYear, "Возрастная");
                break;
            case 2:
                PrintHistogram<Person, int>(mySet, getHeight, "Ростовая");
                break;
            case 3:
                PrintHistogram<Person, int>(mySet, getWeight, "Весовая");
                break;
            default:
                std::cout << "Неверный выбор.\n";
                break;
            }
            break;
        }
        case 'N': {
            std::cout << "Дубликаты не удалялись." << std::endl;
            break;
        }
        default:
            std::cout << "Неверный ввод. Введите 'Y' или 'N'." << std::endl;
            break;
        }
    } else {
        std::cout << "Ввод отсутствует." << std::endl;
    }

    // Работа с отсортированной последовательностью
    ISortedSequence<Person> sortedSeq(persons, CompareBirthYear);
    int variant = 0;
    std::cout << "Без удаления дубликатов:\n";
    std::cout << "Выберите гистограмму: 1 - Возраст, 2 - Рост, 3 - Вес\n";
    std::cin >> variant;

    switch (variant) {
    case 1:
            PrintHistogram<Person, int>(sortedSeq, getBirthYear, "Возрастная");
        break;
    case 2:
        PrintHistogram<Person, int>(sortedSeq, getHeight, "Ростовая");
        break;
    case 3:
        PrintHistogram<Person, int>(sortedSeq, getWeight, "Весовая");
        break;
    default:
        std::cout << "Неверный выбор.\n";
        break;
    }
}


void InterfaceForHistogramNumber(int change) {
    LinkedList<int> numbers;

    // Ввод 10 чисел пользователем
    std::cout << "Введите 10 чисел:\n";
    for (int i = 0; i < 10; ++i) {
        int num;
        std::cin >> num;
        numbers.PushFront(num);
    }

    // Лямбда-функция для получения значения числа
    auto getValue = [](const int& x) -> int { return x; };

    if (change == 1) {
        ISet<int> mySet(numbers);

        if (numbers.GetLength() == 0) {
            std::cout << "Нет данных для обработки.\n";
            return;
        }

        // Минимальное и максимальное значения
        std::cout << "Минимальное значение: " << mySet.GetHead() << std::endl;
        std::cout << "Максимальное значение: " << mySet.GetTail() << std::endl;

        // Печать гистограммы
        PrintHistogram<int, int, decltype(getValue)>(mySet, getValue, "Числа");
        std::cout << "---------------------------------------" << std::endl;
    }

    // Работа с отсортированной последовательностью
    ISortedSequence<int> sortedSeq(numbers, AscendingInt);

    if (numbers.GetLength() == 0) {
        std::cout << "Нет данных для обработки.\n";
        return;
    }

    // Минимальное и максимальное значения
    std::cout << "Минимальное значение: " << sortedSeq.GetHead() << std::endl;
    std::cout << "Максимальное значение: " << sortedSeq.GetTail() << std::endl;

    // Печать гистограммы
    PrintHistogram<int, int, decltype(getValue)>(sortedSeq, getValue, "Числа");
    std::cout << "---------------------------------------" << std::endl;
}





































/*
#include <iomanip>
void interface_for_histogram_number(int change) {
    LinkedList<int> numbers;

    std::cout << "¬‚Â‰ËÚÂ 10 ˜ËÒÂÎ:\n";
    for (int i = 0; i < 10; ++i) {
        int num;
        std::cin >> num;
        numbers.Append(num);
    }

    // ≈ÒÎË ÚÂ·ÛÂÚÒˇ ËÁÏÂÌËÚ¸ ‰‡ÌÌ˚Â, Ì‡ÔËÏÂ, Û‰‡ÎËÚ¸ ‰Û·ÎËÍ‡Ú˚
    if (change == 1) {
        ISet<int> sortedSeq(numbers);
        // œÂ‰ÔÓÎ‡„‡ÂÚÒˇ, ˜ÚÓ ISet<int> Û‰‡ÎˇÂÚ ‰Û·ÎËÍ‡Ú˚ ËÁ numbers
        // Õ‡ÔËÏÂ:
        // mySet.RemoveDuplicates();
        // »ÎË ‰Û„‡ˇ ÌÂÓ·ıÓ‰ËÏ‡ˇ Ó·‡·ÓÚÍ‡
    }
    ISet<int> sortedSeq(numbers);
    // —ÓÁ‰‡∏Ï ÓÚÒÓÚËÓ‚‡ÌÌÛ˛ ÔÓÒÎÂ‰Ó‚‡ÚÂÎ¸ÌÓÒÚ¸ ÔÓÒÎÂ Ó·‡·ÓÚÍË
    //ISortedSequence<int> sortedSeq(numbers, AscendingInt);

    if (sortedSeq.GetLength() == 0) {
        std::cout << "ÕÂÚ ‰‡ÌÌ˚ı ‰Îˇ ÓÚÓ·‡ÊÂÌËˇ ÔÓÒÎÂ Ó·‡·ÓÚÍË.\n";
        return;
    }

    // ¬˚‚Ó‰ ÏËÌËÏ‡Î¸ÌÓ„Ó Ë Ï‡ÍÒËÏ‡Î¸ÌÓ„Ó ÁÌ‡˜ÂÌËÈ
    std::cout << "ÃËÌËÏ‡Î¸ÌÓÂ ÁÌ‡˜ÂÌËÂ: " << sortedSeq.GetFirstElement() << std::endl;
    std::cout << "Ã‡ÍÒËÏ‡Î¸ÌÓÂ ÁÌ‡˜ÂÌËÂ: " << sortedSeq.GetLastElement() << std::endl;

    // –Â‡ÎËÁ‡ˆËˇ „ËÒÚÓ„‡ÏÏ˚ ‚ÌÛÚË ÙÛÌÍˆËË

    std::cout << "\n√ËÒÚÓ„‡ÏÏ‡ ‡ÒÔÂ‰ÂÎÂÌËˇ ˜ËÒÂÎ:\n";
    std::cout << "---------------------------------\n";

    // œÓÒÍÓÎ¸ÍÛ ÔÓÒÎÂ‰Ó‚‡ÚÂÎ¸ÌÓÒÚ¸ ÓÚÒÓÚËÓ‚‡Ì‡, ÏÓÊÌÓ ÔÓÈÚËÒ¸ ÔÓ ÌÂÈ Ó‰ËÌ ‡Á Ë ÔÓ‰Ò˜ËÚ‡Ú¸ ˜‡ÒÚÓÚ˚
    int currentNumber = sortedSeq.GetElement(0);
    int count = 1;

    for (int i = 1; i < sortedSeq.GetLength(); ++i) {
        int num = sortedSeq.GetElement(i);
        if (num == currentNumber) {
            count++;
        }
        else {
            // ¬˚‚Ó‰ ÚÂÍÛ˘Â„Ó ˜ËÒÎ‡ Ë ÒÓÓÚ‚ÂÚÒÚ‚Û˛˘Â„Ó ÍÓÎË˜ÂÒÚ‚‡ Á‚ÂÁ‰Ó˜ÂÍ
            std::cout << std::setw(5) << currentNumber << " | ";
            for (int j = 0; j < count; ++j) {
                std::cout << "*";
            }
            std::cout << " (" << count << ")\n";

            // Œ·ÌÓ‚ÎÂÌËÂ ÚÂÍÛ˘Â„Ó ˜ËÒÎ‡ Ë Ò·ÓÒ Ò˜∏Ú˜ËÍ‡
            currentNumber = num;
            count = 1;
        }
    }

    // ¬˚‚Ó‰ ÔÓÒÎÂ‰ÌÂ„Ó ˜ËÒÎ‡
    std::cout << std::setw(5) << currentNumber << " | ";
    for (int j = 0; j < count; ++j) {
        std::cout << "*";
    }
    std::cout << " (" << count << ")\n";

    std::cout << "---------------------------------\n\n";
    std::cout << "---------------------------------------" << std::endl;
}*/


/*
template <typename T>
void pprint(seq<T>& seq, const std::string& label) {
    int count = seq.getLength();

    if (count == 0) {
        std::cout << label << " Histogram: No data available.\n";
        return;
    }

    // Õ‡ıÓ‰ËÏ min Ë max
    T first_value = seq.getElement(0);
    T max_value = first_value;
    T min_value = first_value;

    for (int i = 1; i < count; ++i) {
        T value = seq.getElement(i);
        if (value > max_value) {
            max_value = value;
        }
        if (value < min_value) {
            min_value = value;
        }
    }

    // ≈ÒÎË ‚ÒÂ ÁÌ‡˜ÂÌËˇ Ó‰ËÌ‡ÍÓ‚˚, ÚÓ Ò‰ÂÎ‡ÂÏ ËÌÚÂ‚‡Î ‡‚Ì˚Ï 1
    int diff = max_value - min_value;
    int interval_size = diff / 10 + 1;

    std::cout << label << " Histogram:\n";

    // »ÌËˆË‡ÎËÁËÛÂÏ ÒÔËÒÓÍ ˜‡ÒÚÓÚ 10 ËÌÚÂ‚‡ÎÓ‚ ÌÛÎˇÏË
    LinkedList<int> frequencies;
    for (int i = 0; i < 10; ++i) {
        frequencies.Append(0);
    }

    // «‡ÔÓÎÌˇÂÏ ˜‡ÒÚÓÚ˚
    for (int i = 0; i < count; ++i) {
        T value = seq.getElement(i);
        int index = (value - min_value) / interval_size;
        if (index >= 10) index = 9; // Œ·‡·ÓÚÍ‡ ‚ÂıÌÂÈ „‡ÌËˆ˚
        frequencies[index] = frequencies[index] + 1;
    }

    // ¬˚‚Ó‰ËÏ „ËÒÚÓ„‡ÏÏÛ
    for (int i = 0; i < 10; ++i) {
        int range_min = min_value + i * interval_size;
        int range_max = min_value + (i + 1) * interval_size - 1;
        // ≈ÒÎË ‚˚ ıÓÚËÚÂ ˜ÚÓ·˚ ‚ÂıÌˇˇ „‡ÌËˆ‡ ·˚Î‡ ‚ÍÎ˛˜ËÚÂÎ¸ÌÓ ·ÂÁ -1, Û·ÂËÚÂ "- 1"
        // ˝ÚÓ Á‡‚ËÒËÚ ÓÚ ÚÓ„Ó, Í‡Í ‚˚ ıÓÚËÚÂ ÓÚÓ·‡ÁËÚ¸ ËÌÚÂ‚‡Î˚

        std::cout << range_min << " - " << range_max << " | ";

        int freq = frequencies[i];
        if (freq > 0) {
            for (int j = 0; j < freq; ++j) {
                std::cout << "x";
            }
        }
        else {
            std::cout << "-";
        }

        std::cout << "\n";
    }
}
*/
