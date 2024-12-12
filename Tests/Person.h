#pragma once

#include <iostream>  // Для ввода/вывода
#include <string>    // Для std::string
#include <iomanip>   // Для __quoted и std::setprecision
#include <ios>
using namespace std;

struct Person {
    int id;
    string firstName;
    string lastName;
    int birthYear;
    double height;
    double weight;

    Person() : id(0), firstName(""), lastName(""), birthYear(0), height(0.0), weight(0.0) {}

    Person(int id, const string& firstName,const string& lastName, int birthYear, double height, double weight)
        : id(id), firstName(firstName), lastName(lastName), birthYear(birthYear), height(height), weight(weight) {}

    friend istream& operator>>(istream& inStream, Person& person) {
        string prefix;
        inStream >> prefix; // Считываем "PERSON:"
        if (prefix != "PERSON:") {
            inStream.setstate(ios::failbit); // Устанавливаем ошибку, если формат не совпадает
            return inStream;
        }

        char comma; // Для пропуска запятых
        string firstName, lastName;

        if (inStream
            >> person.id            // Считываем id
            >> comma                // Пропускаем запятую
            >> __quoted(firstName)     // Считываем FirstName в кавычках
            >> comma                // Пропускаем запятую
            >> __quoted(lastName)     // Считываем LastName в кавычках
            >> comma                // Пропускаем запятую
            >> person.birthYear     // Считываем год рождения
            >> comma                // Пропускаем запятую
            >> person.height        // Считываем рост
            >> comma                // Пропускаем запятую
            >> person.weight) {     // Считываем вес
            person.firstName = firstName;
            person.lastName = lastName;
            } else {
                inStream.setstate(ios::failbit); // Если произошла ошибка при чтении
            }

        return inStream;
    }

    friend std::ostream& operator<<(std::ostream& outStream, const Person& person) {
        outStream << "PERSON: "
           << person.id << " , "
           << __quoted(person.firstName) << " , "
           << __quoted(person.lastName) << " , "
           << person.birthYear << " , "
           << fixed << setprecision(2) << person.height << " , "
           << fixed << setprecision(2) << person.weight;
        return outStream;
    }
};

inline bool AscendingInt(const int& first, const int& second) {return first < second;}

inline bool DescendingInt(const int& first, const int& second) {return first > second;}

inline bool CompareFirstName(const Person& a, const Person& b) {return a.firstName < b.firstName;}

inline bool CompareLastName(const Person& a, const Person& b) {return a.lastName < b.lastName;}

inline bool CompareId(const Person& a, const Person& b) {return a.id > b.id;}

inline bool CompareHeight(const Person& a, const Person& b) {return a.height < b.height;}
