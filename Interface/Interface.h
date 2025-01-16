#pragma once

#include "../Histogram/Histogram.h"
#include "../Tests/LoadTestsCache.h"
#include "../Tests/TestsCache.h"

void interface() {
    int choice;
    bool Run = true;
    
    while (Run) {
        cout << "\nВыберите опцию:" << endl;
        cout << "1) Интерфейс для гистограммы людей" << endl;
        cout << "2) Интерфейс для гистограммы числа" << endl;
        cout << "3) Интерфейс для кэша" << endl;
        cout << "0) Выход" << endl;
        
        cout << "Введите номер выбора: ";
        cin >> choice;
        
        switch(choice)
        {
            case 1:{
                cout << "Гистограмма людей." << endl;
                // Здесь может быть код для работы с гистограммой людей
                InterfaceForHistogramPeople();
                break;
            }
                
            case 2:{
                cout << "Гистограмма числа." << endl;
                
                // Дополнительный выбор для работы с множеством Iset
                int isetChoice;
                cout << "Удалить дубликаты из чисел (использовать множество ISetSequence)? (1 - да, 0 - нет): ";
                cin >> isetChoice;
                
                
                if (isetChoice == 1) {
                    cout << "Вывод гистограммы с множеством ISetSequence (с удалением дубликатов)." << endl;
                    InterfaceForHistogramNumber(true);  // Вызов с удалением дубликатов
                }
                else if (isetChoice == 0) {
                    cout << "Вывод отсортированной гистограммы" << endl;
                    InterfaceForHistogramNumber(false);  // Вызов без удаления дубликатов
                }
                else {
                    cout << "Неверный выбор. Попробуйте снова." << endl;
                }
                break;
            }
                
            case 3:{
                cout << "Проверка работы кэша" << endl;
                
                int cacheChoice;
                cout << "Выберите опцию для работы с кэшем:" << endl;
                cout << "1. Тестирование работы кэша" << endl;
                cout << "2. Выполнение операций с кэшем" << endl;
                cout << "Введите номер выбора: ";
                cin >> cacheChoice;
                
                switch (cacheChoice) {
                    case 1:
                        runCacheTest();
                        break;
                    case 2:
                        runCacheOperations();
                        break;
                    default:
                        cout << "Неверный выбор. Попробуйте снова." << endl;
                        break;
                        
                }
                break;
            }
                
            case 0:{
                cout << "Выход из программы..." << endl;
                Run = false;
                break;
            }
                
            default: {
                cout << "Неверный выбор. Попробуйте снова." << endl;
                break;
            }
                
                
        }
    }
}
