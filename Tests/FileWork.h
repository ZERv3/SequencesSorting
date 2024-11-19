#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

void WriteRandomNumbersToFile(unsigned long long quantity, const std::string& outputFileName);

template <typename T>
void ReadData(const std::string& fileName, LinkedList<T>& list) {
    std::ifstream inFile(fileName); // Ñîçäàåì îáúåêò äëÿ ÷òåíèÿ èç ôàéëà
    if (!inFile) {
        std::cerr << "Error opening the file: " << fileName << std::endl;
        return; // Åñëè ôàéë íå îòêðûëñÿ, âûõîäèì èç ôóíêöèè
    }

    T value;
    // ×èòàåì äàííûå èç ôàéëà
    while (inFile >> value) {
        list.Append(value); // Äîáàâëÿåì êàæäîå ñ÷èòàííîå çíà÷åíèå â ñïèñîê
    }

    inFile.close(); // Çàêðûâàåì ôàéë
}

template <typename T>
void ReadData(const std::string& fileName, DynamicArray<T>& array) {
    std::ifstream inFile(fileName); // Îòêðûâàåì ôàéë äëÿ ÷òåíèÿ
    if (!inFile) {
        std::cerr << "Error opening the file: " << fileName << std::endl;
        return; // Åñëè ôàéë íå îòêðûëñÿ, âûõîäèì èç ôóíêöèè
    }

    T value;
    // ×èòàåì äàííûå èç ôàéëà
    while (inFile >> value) {
        array.Append(value); // Äîáàâëÿåì êàæäîå ñ÷èòàííîå çíà÷åíèå â ìàññèâ
    }

    inFile.close(); // Çàêðûâàåì ôàéë
}

template <typename T>
void ReadNumbersFromFile(const std::string& inputFileName, Sequence<T>& numbers) {
    std::ifstream fileStream(inputFileName); // Ñîçäàåì îáúåêò äëÿ ÷òåíèÿ èç ôàéëà

    if (!fileStream.is_open()) { // Ïðîâåðÿåì, îòêðûëñÿ ëè ôàéë
        std::cerr << "Error opening file: " << inputFileName << std::endl;
        return; // Åñëè ôàéë íå îòêðûëñÿ, çàâåðøàåì ôóíêöèþ
    }

    std::string line;

    // ×èòàåì ñòðîêè èç ôàéëà
    while (std::getline(fileStream, line)) {
        if (line.size() > 300) { // Ïðîâåðêà, íå ïðåâûøàåò ëè ñòðîêà 300 áàéò
            std::cerr << "Error: Line exceeds 300 bytes: " << line << std::endl;
            continue; // Ïðîïóñòèòü ñòðîêè, ïðåâûøàþùèå 300 áàéò
        }

        std::istringstream iss(line);
        T item;

        // Ïîïûòêà ïðî÷èòàòü ñòðîêó â íóæíûé òèï
        if (iss >> item) {
            numbers.Append(item); // Äîáàâëÿåì ýëåìåíò â ïîñëåäîâàòåëüíîñòü
        }
        else {
            std::cerr << "Error: Could not convert line to target type: " << line << std::endl;
        }
    }

    fileStream.close(); // Çàêðûâàåì ôàéë
}



template <class T>
void WriteSequenceToFile(std::string& fileName, Sequence<T>* numbers)
{
    std::ofstream outFile(fileName);
    if (!outFile) {
        std::cerr << "Error opening the file!" << std::endl;
        return;
    }

    auto begin = numbers->ToBegin();
    auto end = numbers->ToEnd();

    while (*begin != *end)
    {
        outFile << **begin << std::endl;
        ++(*begin);
    }

    std::cout << "The numbers have been successfully written to the file " << fileName << std::endl;

    outFile.close();
}