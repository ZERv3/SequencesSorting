#include <iostream>
#include <fstream>
#include <random>
#include "IntegerDataGenerator.h"

bool GenerateIntegersToFile(int minVal, int maxVal, int count, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Не удалось открыть файл " << filename << " для записи." << std::endl;
        return false;
    }

    // Инициализация генератора случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(minVal, maxVal);

    for (int i = 0; i < count; ++i) {
        int num = dist(gen);
        outFile << num << "\n";
    }

    return true;
}
